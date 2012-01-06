#include <ldc/types.h>
#include <ldc/info.h>

int main(void) {
	struct device *dev = new_device("Plugin");
	get_info(dev);
	print_device_list(dev);

	free_device(&dev);

	return 0;
}
