#pragma once

#include <map>
#include <string>
#include <vector>

namespace Udev
{
	using UdevHandle = struct udev;
	using UdevMonitorHandle = struct udev_monitor;
	using UdevDeviceHandle = struct udev_device;
	using UdevEnumerateHandle = struct udev_enumerate;

	class UdevMonitor;
	class UdevDevice;
	class UdevEnumerate;

	class Udev
	{
	public:
		explicit Udev();
		Udev(const Udev& other);
		Udev(Udev&& other);
		Udev& operator=(const Udev& other);
		Udev& operator=(Udev&& other);
		~Udev();

		UdevMonitor monitor_new_from_netlink(const char *name = "udev");
		UdevEnumerate enumerate_new();
	private:
		UdevHandle *handle;
	};

	class UdevMonitor
	{
	public:
		UdevMonitor(UdevMonitorHandle *monitor);
		UdevMonitor(const UdevMonitor &other);
		UdevMonitor(UdevMonitor &&other);
		UdevMonitor& operator=(const UdevMonitor &monitor);
		UdevMonitor& operator=(UdevMonitor &&monitor);
		~UdevMonitor();

		void enable_receiving() const;
		int get_fd() const;

		UdevDevice receive_device() const;
	private:
		UdevMonitorHandle *handle;
	};

	class UdevEnumerate
	{
	public:
		UdevEnumerate(UdevEnumerateHandle *enumerate);
		UdevEnumerate(const UdevEnumerate &other);
		UdevEnumerate(UdevEnumerate &&other);
		UdevEnumerate &operator=(const UdevEnumerate &other);
		UdevEnumerate &operator=(UdevEnumerate &&other);
		~UdevEnumerate();

		void add_match_subsystem(const std::string subsystem) const;
		void add_nomatch_subsystem(const std::string subsystem) const;

		void add_match_sysattr(const std::string sysattr, const std::string value = "") const;
		void add_nomatch_sysattr(const std::string sysattr, const std::string value = "") const;

		void add_match_property(const std::string property, const std::string value) const;

		void add_match_tag(const std::string tag) const;

		void add_match_is_initialized() const;

		void scan_devices() const;
		void scan_subsystems() const;

		std::vector<UdevDevice> enumerate_devices() const;
	private:
		UdevEnumerateHandle *handle;
	};


	class UdevDevice
	{
	public:
		UdevDevice(UdevDeviceHandle *device);
		UdevDevice(const UdevDevice &);
		UdevDevice(UdevDevice &&);
		UdevDevice& operator=(const UdevDevice &);
		UdevDevice& operator=(UdevDevice &&);
		~UdevDevice();

		bool is_initialized() const;

		bool has_action() const;
		std::string get_action() const;

		bool has_devnode() const;
		std::string get_devnode() const;

		bool has_devtype() const;
		std::string get_devtype() const;

		bool has_subsystem() const;
		std::string get_subsystem() const;

		std::string get_devpath() const;
		std::string get_syspath() const;
		std::string get_sysname() const;

		bool has_sysnum() const;
		std::string get_sysnum() const;

		bool has_driver() const;
		std::string get_driver() const;

		bool has_sysattr(const std::string named) const;
		std::string get_sysattr(const std::string named) const;
		std::vector<std::string> get_sysattr_keys() const;
		std::map<std::string, std::string> get_sysattr_map() const;

		std::vector<std::string> get_devlinks() const;

		bool has_property(const std::string named) const;
		std::string get_property(const std::string named) const;
		std::map<std::string, std::string> get_properties() const;

		bool has_tag(const std::string named) const;
		std::vector<std::string> get_tags() const;

	private:
		UdevDeviceHandle *handle;
	};
}