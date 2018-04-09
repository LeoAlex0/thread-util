aux_source_directory(. LOCAL_SRC)

add_library(thread SHARED ${LOCAL_SRC} ../include/Semaphore.h ../include/Traits.h)