#include "device_common.h"
static const flash_info_t Flash_8051[] = {
// N76E885
{18 * 1024, 0, 0x0100, 0x00002150, ((0 << 25) | (0 << 24) | (0x0E << 8) | (0 << 7) | (0 << 6) | (0 << 5) | (0 << 4) | (0 << 2) | (0 << 0))},
{18 * 1024, 0, 0x0100, 0x00002140, ((0 << 25) | (0 << 24) | (0x0E << 8) | (0 << 7) | (0 << 6) | (0 << 5) | (0 << 4) | (0 << 2) | (1 << 0))},
// N76E616
{18 * 1024, 0, 0x0100, 0x00002F50, ((0 << 25) | (0 << 24) | (0x0E << 8) | (0 << 7) | (0 << 6) | (0 << 5) | (0 << 4) | (1 << 2) | (0 << 0))},
// N76E003
{18 * 1024, 0, 0x0300, 0x00003650, ((0 << 25) | (0 << 24) | (0x0E << 8) | (0 << 7) | (0 << 6) | (0 << 5) | (0 << 4) | (0 << 2) | (0 << 0))},
{18 * 1024, 0, 0x0300, 0x00003640, ((0 << 25) | (0 << 24) | (0x0E << 8) | (0 << 7) | (0 << 6) | (0 << 5) | (0 << 4) | (0 << 2) | (1 << 0))},
// N76L151
//{ 32*1024, 0, 0x1000, 0x00003E60, 0},
//{ 32*1024, 0, 0x0800, 0x00003E61, 0},
// ML51
{8 * 1024,  0, 0x0400, 0x00004711, ((0 << 25) | (1 << 24) | (0x0F << 8) | (0 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
{16 * 1024, 0, 0x0400, 0x00004721, ((0 << 25) | (1 << 24) | (0x0F << 8) | (0 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
{16 * 1024, 0, 0x0400, 0x00004821, ((0 << 25) | (1 << 24) | (0x0F << 8) | (0 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
{32 * 1024, 0, 0x0800, 0x00004832, ((0 << 25) | (1 << 24) | (0x0F << 8) | (0 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
{32 * 1024, 0, 0x0800, 0x00004932, ((0 << 25) | (1 << 24) | (0x0F << 8) | (0 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
{64 * 1024, 0, 0x1000, 0x00004944, ((0 << 25) | (1 << 24) | (0x0F << 8) | (0 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
// MS51
{8 * 1024,  0, 0x0200, 0x00004B10, ((0 << 25) | (1 << 24) | (0x0E << 8) | (0 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
{8 * 1024,  0, 0x0400, 0x00004B11, ((0 << 25) | (1 << 24) | (0x0E << 8) | (0 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
{16 * 1024, 0, 0x0200, 0x00004B20, ((0 << 25) | (1 << 24) | (0x0E << 8) | (0 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
{16 * 1024, 0, 0x0400, 0x00004B21, ((0 << 25) | (1 << 24) | (0x0E << 8) | (0 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
{8 * 1024,  0, 0x0400, 0x00005211, ((0 << 25) | (1 << 24) | (0x0E << 8) | (0 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
{16 * 1024, 0, 0x0800, 0x00005322, ((0 << 25) | (1 << 24) | (0x0E << 8) | (0 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
{32 * 1024, 0, 0x0800, 0x00005332, ((0 << 25) | (1 << 24) | (0x0E << 8) | (0 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
// ML56
{32 * 1024, 0, 0x1000, 0x00005734, ((1 << 25) | (1 << 24) | (0x07 << 8) | (1 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
{64 * 1024, 0, 0x1000, 0x00005744, ((1 << 25) | (1 << 24) | (0x07 << 8) | (1 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
// MUG51
{16 * 1024, 0, 0x0400, 0x00006321, ((1 << 25) | (1 << 24) | (0x0F << 8) | (0 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
// MG51, N76S003
//{ 18*1024, 0, 0x0300, 0x00006750, ((0 << 25) | (0 << 24) | (0x0E << 8) | (0 << 7) | (0 << 6) | (0 << 5) | (0 << 4) | (0 << 2) | (0 << 0))},
{18 * 1024, 0, 0x0400, 0x00006750, ((0 << 25) | (0 << 24) | (0x0E << 8) | (0 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
{16 * 1024, 0, 0x0400, 0x00006721, ((0 << 25) | (1 << 24) | (0x0E << 8) | (0 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))},
{32 * 1024, 0, 0x0400, 0x00006731, ((0 << 25) | (1 << 24) | (0x0E << 8) | (0 << 7) | (1 << 6) | (1 << 5) | (1 << 4) | (0 << 2) | (0 << 0))}
};



const flash_info_t * get_flash_info(uint32_t DID)
{
    for (int i = 0; i < sizeof(Flash_8051) / sizeof(flash_info_t); i++)
    {
        if (Flash_8051[i].DID == DID)
        {
            return &Flash_8051[i];
        }
    }
    return 0;
}

uint32_t flash_info_get_aprom_size(const flash_info_t *flash_info, uint32_t ldrom_size){
    uint32_t max_nvm_size = flash_info_get_max_nvm_size(flash_info);
    if (max_nvm_size > 0)
        return flash_info->memory_size - max_nvm_size;
    return flash_info->memory_size - ldrom_size;
}

uint32_t flash_info_get_max_nvm_size(const flash_info_t * flash_info)
{
    if (flash_info->Flash_type & 0x3){
        return 0x2800;
    }
    return 0;
}