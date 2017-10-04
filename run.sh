#!/bin/sh
export DYLD_LIBRARY_PATH=.;
export DYLD_INSERT_LIBRAIRIES="libft_malloc.so";
export DYLD_FORCE_FLAT_NAMESPACES=1;
$@;
