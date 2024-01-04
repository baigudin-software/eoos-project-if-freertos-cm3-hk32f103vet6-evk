/**
 * @file      DriverCanTest.cpp
 * @author    Sergey Baigudin, sergey@baigudin.software
 * @copyright 2023-2024, Sergey Baigudin, Baigudin Software
 *
 * @brief Tests of CAN driver.
 */
#include "DriverCanTest.hpp"
#include "drv.Can.hpp"
#include "lib.UniquePointer.hpp"

namespace eoos
{

void testDriverCan()
{
    drv::Can::Config config = {
        .number = drv::Can::NUMBER_CAN1,
        .reg    = {
            .mcr = {
                .txfp = 0,
                .rflm = 0,
                .nart = 0,
                .awum = 0,
                .abom = 0,
                .ttcm = 0
            },
            .btr = {
                .brp  = 0,
                .ts1  = 0,
                .ts2  = 0,
                .sjw  = 0,
                .lbkm = 1,
                .silm = 0
            }
        }
    };
    lib::UniquePointer<drv::Can> can( drv::Can::create(config) );
}

} // namespace eoos
