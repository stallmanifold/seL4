/*
 * Copyright 2017, General Dynamics C4 Systems
 *
 * This software may be distributed and modified according to the terms of
 * the GNU General Public License version 2. Note that NO WARRANTY is provided.
 * See "LICENSE_GPLv2.txt" for details.
 *
 * @TAG(GD_GPL)
 */

#ifndef __MODE_KERNEL_THREAD_H
#define __MODE_KERNEL_THREAD_H

static inline word_t
sanitiseRegister(register_t reg, word_t v, tcb_t *thread)
{
    if (reg == CPSR) {
#ifdef CONFIG_ARM_HYPERVISOR_SUPPORT
        if (thread->tcbArch.vcpu) {
            switch (v & 0x1f) {
            case PMODE_USER:
            case PMODE_FIQ:
            case PMODE_IRQ:
            case PMODE_SUPERVISOR:
            case PMODE_ABORT:
            case PMODE_UNDEFINED:
            case PMODE_SYSTEM:
                return v;
            case PMODE_HYPERVISOR:
            default:
                /* For backwards compatibility, Invalid modes revert to USER mode */
                break;
            }
        }
#endif /* CONFIG_ARM_HYPERVISOR_SUPPORT */

        return (v & 0xf8000000) | CPSR_USER;
    } else {
        return v;
    }
}

#endif
