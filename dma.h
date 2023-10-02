
#ifndef DMA_H_
#define DMA_H_

//#define DMA_BASE_ADDR   ((volatile uint32_t *)0x20000000U)

typedef struct
{
    volatile uint32_t srcEndPtr;
    volatile uint32_t dstEndPtr;
    volatile uint32_t controlWord;
    volatile uint32_t unused;
} controlStructure_t;

extern controlStructure_t dmaControlBlockMem[0x3F0] __attribute__ ((aligned (1024)));
void initDma(void);
void checkMyDmaTransfer(void);
void DmaBusError(void);

#endif
