#
# Component Makefile
#

COMPONENT_OBJS := block_map.o cluster_group.o heap_block.o heap_caps.o heap_caps_init.o memory_layout.o memory_layout_utils.o multi_heap.o offset_index.o parent_group.o

ifdef CONFIG_HEAP_TRACING

WRAP_FUNCTIONS = calloc malloc free realloc heap_caps_malloc heap_caps_free heap_caps_realloc heap_caps_malloc_default heap_caps_realloc_default
WRAP_ARGUMENT := -Wl,--wrap=

COMPONENT_ADD_LDFLAGS = -l$(COMPONENT_NAME) $(addprefix $(WRAP_ARGUMENT),$(WRAP_FUNCTIONS))

endif

COMPONENT_ADD_LDFRAGMENTS += linker.lf

CFLAGS += -DMULTI_HEAP_FREERTOS
