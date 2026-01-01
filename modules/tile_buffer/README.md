# Tile buffer module
Small framebuffer in BRAM to hold 128x64 pixel data to enable tiled-rasterization. 
Each pixel in the tilebuffer stores:
- 3 * 16 bit for R, G and B color channels
- 24 bit depth data
Implemented using two UltraRAM blocks, each of which are 4k * 72 bit. URAM0 stores
all even x-positions and URAM1 stores all odd x-positions. Each URAM block is dual-ported
enabling two simultanious reads/writes to different positions in each URAM block. Read in 
parallel when flushing to system memory.
