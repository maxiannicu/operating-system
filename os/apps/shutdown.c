#include "shutdown.h"
#include "../drivers/acpi.h"
#include "../modules/io.h"

void shutdown_start(){
	io_printf("Shutting down...\n");
	acpi_shutdown();
}
