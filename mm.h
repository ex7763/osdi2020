#ifndef _MM_H_
#define _MM_H_

#define PBASE 0x3F000000
#define PAGE_SHIFT 12
#define TABLE_SHIFT 9
#define SECTION_SHIFT (PAGE_SHIFT + TABLE_SHIFT)

#define PAGE_SIZE (1 << PAGE_SHIFT)
#define SECTION_SIZE (1 << SECTION_SHIFT)

#define LOW_MEMORY (2 * SECTION_SIZE)
#define HIGH_MEMORY PBASE

#define PAGING_MEMORY (HIGH_MEMORY - LOW_MEMORY)
#define PAGING_PAGES (PAGING_MEMORY / PAGE_SIZE)

#define THREAD_SIZE PAGE_SIZE

#define PAGESIZE 4096
#define PAGE (PAGESIZE / 8)

// granularity
#define PT_TABLE 0b11
#define PT_PAGE 0b11
#define PT_BLOCK 0b01

// accessibility
#define PT_KERNEL (0 << 6) // privileged, supervisor EL1 access only
#define PT_USER (1 << 6)   // unprivileged, EL0 access allowed
#define PT_RW (0 << 7)     // read-write
#define PT_RO (1 << 7)     // read-only
#define PT_AF (1 << 10)    // accessed flag
#define PT_NX (1UL << 54)  // no execute
// shareability
#define PT_OSH (2 << 8) // outter shareable
#define PT_ISH (3 << 8) // inner shareable
// defined in MAIR register
#define PT_MEM (0 << 2) // normal memory
#define PT_DEV (1 << 2) // device MMIO
#define PT_NC (2 << 2)  // non-cachable

#define TTBR_CNP 1
#define PTE_SHIFT 12

void mmu_init();

unsigned long pa_to_pfn(unsigned long pa);

unsigned long va_to_pa(unsigned long va);

unsigned long pfn_to_pa(unsigned long pfn);

#define MB256 (1 << 28)
#define MB512 (1 << 29)

// one page have 4K = 0x1000 = 4096
typedef struct mem_page_t
{
    unsigned char c[PAGE_SIZE];
} mem_page_t;

/*
static mem_page_t mem_map[1024] = {
    0,
};
*/

/*
static mem_page_t u_mem_map[1024] = {
    0,
};
*/

//static const unsigned long mem_map_pa = (unsigned long)&mem_map[1];
static const unsigned long mem_map_pa = (unsigned long)MB256;

static const unsigned long u_mem_map_pa = (unsigned long)MB512;

unsigned long get_free_page();

void free_page(unsigned long p);

void mem_map_init();

int mm_remain_page_num();

#endif