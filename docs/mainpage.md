Introduction
============

The PMSIS API is a set of low-level drivers which any operating system can implement to provide a common layer to upper layers. Together with the PMSIS BSP, it provides a full stack of drivers, allowing the development of applications portable accros a wide rage of operating systems.

Conventions
===========

All functions prefixed by `pi_` can only be called from fabric-controller side while the ones prefixed by `cl_pi_` can only be called from cluster side. Any exception to these rules is documented where it applies.

All functions on fabric-controller side are by default synchronous and are blocking the caller until the operation is done. All the functions suffixed by `_async` are asynchronous and are not blocking the caller. The termination of such operations is managed with a `pi_task_t` object, see PMSIS API documentation for more information.

Functions on cluster-side are by default synchronous but can also be asynchronous if the documentation of the function mentions it.

Chip-specific information
=========================

GAP8
----

All functions transfering data between an external device and a chip memory must use the L2 memory for the chip memory.