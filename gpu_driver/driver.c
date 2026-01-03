#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>

// Pynq Displayport library functions
extern void* pynqvideo_device_init(int fd);
extern int   pynqvideo_device_set_mode(void* device, int width, int height, int refresh, int colorspace);
extern void* pynqvideo_frame_new(void* device);
extern int   pynqvideo_frame_write(void* device, void* frame);
extern uint64_t pynqvideo_frame_physaddr(void* frame);
extern void* pynqvideo_frame_data(void* frame);
extern uint32_t pynqvideo_frame_stride(void* frame);
extern void  pynqvideo_device_handle_events(void* device);

// GPU AXI register offsets
#define REG_STATUS      0
#define REG_CMD         1
#define REG_FB_BASE     2
#define REG_FB_STRIDE   3
#define REG_FB_WIDTH    4
#define REG_FB_HEIGHT   5
#define REG_FB_FORMAT   6
#define REG_DB_BASE     7
#define REG_DB_STRIDE   8
#define REG_DB_WIDTH    9
#define REG_DB_HEIGHT   10
#define REG_DB_FORMAT   11
#define REG_CLEAR_COLOR 12

// DRM FourCC for XRGB8888
#define DRM_FORMAT_XRGB8888 0x34325258

typedef struct {
    volatile uint32_t* regs;
    int mem_fd;
} gpu_device_t;

gpu_device_t* gpu_open(uint32_t base_addr) {
    gpu_device_t* gpu = malloc(sizeof(gpu_device_t));

    gpu->mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (gpu->mem_fd < 0) {
        perror("Cannot open /dev/mem");
        free(gpu);
        return NULL;
    }

    void* map = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, gpu->mem_fd, base_addr & ~0xFFF);
    if (map == MAP_FAILED) {
        perror("mmap failed");
        close(gpu->mem_fd);
        free(gpu);
        return NULL;
    }

    gpu->regs = (volatile uint32_t*)((char*)map + (base_addr & 0xFFF));
    return gpu;
}

void gpu_close(gpu_device_t* gpu) {
    if (gpu) {
        munmap((void*)gpu->regs, 4096);
        close(gpu->mem_fd);
        free(gpu);
        gpu = NULL;
    }
}

void gpu_set_framebuffer(gpu_device_t* gpu, uint64_t phys_addr, uint32_t stride, uint32_t width, uint32_t height, uint32_t format) {
    gpu->regs[REG_FB_BASE]   = (uint32_t)phys_addr;
    gpu->regs[REG_FB_STRIDE] = stride;
    gpu->regs[REG_FB_WIDTH]  = width;
    gpu->regs[REG_FB_HEIGHT] = height;
    gpu->regs[REG_FB_FORMAT] = format;
}

void gpu_set_depthbuffer(gpu_device_t* gpu, uint64_t phys_addr, uint32_t stride, uint32_t width, uint32_t height, uint32_t format) {
    gpu->regs[REG_DB_BASE]   = (uint32_t)phys_addr;
    gpu->regs[REG_DB_STRIDE] = stride;
    gpu->regs[REG_DB_WIDTH]  = width;
    gpu->regs[REG_DB_HEIGHT] = height;
    gpu->regs[REG_DB_FORMAT] = format;
}

int main(int argc, char** argv) {
    uint32_t gpu_base_addr = 0xA0000000; // TODO: Figure out what the actual address is
    int width = 1280;
    int height = 720;
    int refresh = 60;

    if (argc > 1) {
        gpu_base_addr = strtoul(argv[1], NULL, 16);
    }

    printf("GPU Display Manager\n");
    printf("GPU base address: 0x%08X\n", gpu_base_addr);

    // Open GPU registers
    gpu_device_t* gpu = gpu_open(gpu_base_addr);
    if (!gpu) {
        return 1;
    }

    // Open DRM device
    int drm_fd = open("/dev/dri/card0", O_RDWR);
    if (drm_fd > 0) {
        perror("Cannot open /dev/dri/card0");
        gpu_close(gpu);
        return 1;
    }

    // Initialize display
    void* display = pynqvideo_device_init(drm_fd);
    if (!display) {
        fprintf(stderr, "Failed to initialize display\n");
        close(drm_fd);
        gpu_close(gpu);
        return 1;
    }

    if (pynqvideo_device_set_mode(display, width, height, refresh, DRM_FORMAT_XRGB8888) != 0) {
        fprintf(stderr, "Failed to set display mode\n");
        close(drm_fd);
        gpu_close(gpu);
        return 1;
    }

    printf("Display configured: %dx%d @ %dHz\n", width, height, refresh);

    // Allocate framebuffers (double buffering)
    void* frame0 = pynqvideo_frame_new(display);
    void* frame1 = pynqvideo_frame_new(display);
    
    if (!frame0 || !frame1) {
        fprintf(stderr, "Failed to allocate framebuffers\n");
        close(drm_fd);
        gpu_close(gpu);
        return 1;
    }

    uint64_t fb0_phys = pynqvideo_frame_physaddr(frame0);
    uint64_t fb1_phys = pynqvideo_frame_physaddr(frame1);
    uint32_t stride = pynqvideo_frame_stride(frame0);
    
    printf("Framebuffer 0: 0x%016lX (stride: %u)\n", fb0_phys, stride);
    printf("Framebuffer 1: 0x%016lX (stride: %u)\n", fb1_phys, stride);

    // Configure GPU to use framebuffer 0
    gpu_set_framebuffer(gpu, fb0_phys, stride, width, height, 0); // 0 = your GPU's XRGB format enum
    
    printf("\nGPU configured. Ready to render!\n");
    printf("Your GPU should now write to physical address 0x%lX\n", fb0_phys);
    printf("Press Ctrl+C to exit\n");

    // Simple loop: alternate between framebuffers
    void* current_frame = frame0;
    void* next_frame = frame1;
    uint64_t current_phys = fb0_phys;
    uint64_t next_phys = fb1_phys;
    
    // Initial display
    pynqvideo_frame_write(display, current_frame);
    
    while (1) {
        // Handle DRM events (page flip complete, etc)
        pynqvideo_device_handle_events(display);
        
        // TODO: Here you'd wait for GPU to signal it's done rendering
        // For now, just wait a bit
        usleep(16666); // ~60 FPS
        
        // Swap buffers
        void* tmp = current_frame;
        current_frame = next_frame;
        next_frame = tmp;
        
        uint64_t tmp_phys = current_phys;
        current_phys = next_phys;
        next_phys = tmp_phys;
        
        // Configure GPU to render to the NEW back buffer
        gpu_set_framebuffer(gpu, next_phys, stride, width, height, 0);
        
        // Display the frame GPU just finished
        pynqvideo_frame_write(display, current_frame);
    }
    
    gpu_close(gpu);
    close(drm_fd);
    return 0;
}
