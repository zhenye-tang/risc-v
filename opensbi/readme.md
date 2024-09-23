# opensbi

## 什么是 SBI？

​	SBI 全称 Supervisor Binary Interface，是 RISC-V 执行环境接口之一，目的是使处于 Supervisor-mode 的程序能够很方便的移植到实现不同扩展指令集的 RISC-V 架构的处理器上。	

​	就是一种规范，规定了 S 模式如何使用 M 模式提供的功能，有了 SBI 之后，只要在扩展指令集不同的 RISC-V 微架构中实现统一的向上的 SBI 接口，上层操作系统就可以不在关注具体的微架构细节，而是专注实现于 SBI 接口提供的功能即可。

​	这个规范拥有多种实现，OpenSBI是它的一种实现，OpenSBI 不仅仅具有加载和引导功能，也能够供 S-Mode 的 OS 使用，比如提供串口控制台或者中断的分发等等。

## 如何编译

  make PLATFORM=generic PLATFORM_RISCV_XLEN=64 CROSS_COMPILE=riscv64-linux-

## 示例简介

​	该示例是一个运行在 S mode 的示例，从 Opensbi 跳转到该程序，并通过 SBI 规范调用 M mode 提供的能力。