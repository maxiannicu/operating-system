#include "acpi.h"
#include "../runtime/ports.h"

void acpi_shutdown(){
	port_byte_out(0xf4, 0x00);
}
