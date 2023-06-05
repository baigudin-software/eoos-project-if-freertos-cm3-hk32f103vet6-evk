;/ ----------------------------------------------------------------------------
;/ @brief Boot routine.
;/
;/ The module initializes HK32F103x MCU and C/C++ run-time environment.
;/
;/ @file      cpu.Boot.keil.s
;/ @author    Sergey Baigudin, sergey@baigudin.software
;/ @copyright 2023, Sergey Baigudin, Baigudin Software
;/ ----------------------------------------------------------------------------

                PRESERVE8
                THUMB

                AREA    |.text|, CODE, READONLY

c_startup
m_bootstrap
                nop
                nop
                nop                
                b       m_bootstrap
                
                END