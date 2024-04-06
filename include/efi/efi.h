#pragma once
/**
 * UEFI Specification: https://uefi.org/specs/UEFI/2.10/
 */

#include <stdint.h>
#include <stddef.h>
#if __has_include(<uchar.h>)
#include <uchar.h>
#else
typedef uint_least16_t char16_t;
#endif

/**
 * Common Types: UEFI Specification 2.10 Section 2.3.1
 */

typedef uint8_t BOOLEAN;
#if __SIZEOF_POINTER__ == 4
typedef int32_t  INTN;
typedef uint32_t UINTN;
#else
typedef int64_t  INTN;
typedef uint64_t UINTN;
#endif

typedef int8_t      INT8;
typedef uint8_t     UINT8;
typedef int16_t     INT16;
typedef uint16_t    UINT16;
typedef int32_t     INT32;
typedef uint32_t    UINT32;
typedef int64_t     INT64;
typedef uint64_t    UINT64;
// typedef int128_t    INT128;
// typedef uint128_t   UINT128;
typedef char        CHAR8;
typedef char16_t    CHAR16;
typedef void        VOID;

typedef struct EFI_GUID EFI_GUID;
typedef UINTN   EFI_STATUS;
typedef VOID*   EFI_HANDLE;
typedef VOID*   EFI_EVENT;
typedef UINT64  EFI_LBA;
typedef UINTN   EFI_TPL;
// TODO EFI_MAC_ADDRESS
// TODO EFI_IPv4_ADDRESS
// TODO EFI_IPv6_ADDRESS
// TODO EFI_IP_ADDRESS

/**
 * Common Type Modifiers: UEFI Specification 2.10 Section 2.3.1
 */
#define IN
#define OUT
#define OPTIONAL
#define EFI_API __attribute__((ms_abi))

/**
 * Structure Typedefs: UEFI Specification 2.10 Section 3
 */
typedef struct EFI_LOAD_OPTION EFI_LOAD_OPTION;

/**
 * Structure Typedefs: UEFI Specification 2.10 Section 4
 */
typedef struct EFI_TABLE_HEADER EFI_TABLE_HEADER;
typedef struct EFI_SYSTEM_TABLE EFI_SYSTEM_TABLE;
typedef struct EFI_BOOT_SERVICES EFI_BOOT_SERVICES;
typedef struct EFI_RUNTIME_SERVICES EFI_RUNTIME_SERVICES;
typedef struct EFI_CONFIGURATION_TABLE EFI_CONFIGURATION_TABLE;

/**
 * Structure Typedefs: UEFI Specification 2.10 Section 9
 */
typedef struct EFI_LOADED_IMAGE_PROTOCOL EFI_LOADED_IMAGE_PROTOCOL;

/**
 * Structure Typedefs: UEFI Specification 2.10 Section 12
 */
typedef struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL;
typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL;
// typedef struct EFI_SIMPLE_TEXT_OUTPUT_EX_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_EX_PROTOCOL;
typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

/**
 * Structure Typedefs: UEFI Specification 2.10 Section 13
 */
typedef struct EFI_LOAD_FILE_PROTOCOL EFI_LOAD_FILE_PROTOCOL;
typedef struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL EFI_SIMPLE_FILE_SYSTEM_PROTOCOL;
typedef struct EFI_FILE_PROTOCOL EFI_FILE_PROTOCOL;
typedef struct EFI_FILE_INFO EFI_FILE_INFO;
typedef struct EFI_FILE_SYSTEM_INFO EFI_FILE_SYSTEM_INFO;
typedef struct EFI_FILE_SYSTEM_VOLUME_LABEL EFI_FILE_SYSTEM_VOLUME_LABEL;

/**
 * GUID: UEFI Specification 2.10 Appendix A
 */
struct __attribute__((__packed__)) EFI_GUID {
    UINT32 TimeLow;
    UINT16 TimeMid;
    UINT16 TimeHighAndVersion;
    UINT8  ClockSequenceHighAndReserved;
    UINT8  ClockSequenceLow;
    UINT8  Node[6];
};

/**
 * EFI_EVENT_NOTIFY: UEFI Specification 2.10 Section 7.1.1
 */
typedef VOID (EFI_API *EFI_EVENT_NOTIFY) (
    IN EFI_EVENT    Event,
    IN VOID         *Context
);

/**
 * EFI_CREATE_EVENT: UEFI Specification 2.10 Section 7.1.1
 */
typedef EFI_STATUS (EFI_API *EFI_CREATE_EVENT) (
    IN UINT32           Type,
    IN EFI_TPL          NotifyTpl,
    IN EFI_EVENT_NOTIFY NotifyFunction OPTIONAL,
    IN VOID             *NotifyContext OPTIONAL,
    OUT EFI_EVENT       *Event
);

#define EVT_TIMER                            0x80000000
#define EVT_RUNTIME                          0x40000000
#define EVT_NOTIFY_WAIT                      0x00000100
#define EVT_NOTIFY_SIGNAL                    0x00000200
#define EVT_SIGNAL_EXIT_BOOT_SERVICES        0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE    0x60000202

/**
 * EFI_CREATE_EVENT_EX: UEFI Specification 2.10 Section 7.1.2
 */
typedef EFI_STATUS (EFI_API *EFI_CREATE_EVENT_EX) (
    IN UINT32           Type,
    IN EFI_TPL          NotifyTpl,
    IN EFI_EVENT_NOTIFY NotifyFunction OPTIONAL,
    IN VOID             *NotifyContext OPTIONAL,
    IN EFI_GUID         *EventGroup OPTIONAL,
    OUT EFI_EVENT       *Event
);

/**
 * EFI_CLOSE_EVENT: UEFI Specification 2.10 Section 7.1.3
 */
typedef EFI_STATUS (EFI_API *EFI_CLOSE_EVENT) (
    IN EFI_EVENT    Event
);

/**
 * EFI_SIGNAL_EVENT: UEFI Specification 2.10 Section 7.1.4
 */
typedef EFI_STATUS (EFI_API *EFI_SIGNAL_EVENT) (
    IN EFI_EVENT    Event
);

/**
 * EFI_WAIT_FOR_EVENT: UEFI Specification 2.10 Section 7.1.5
 */
typedef EFI_STATUS (EFI_API *EFI_WAIT_FOR_EVENT) (
    IN UINTN        NumberOfEvents,
    IN EFI_EVENT    *Event,
    OUT UINTN       *Index
);

/**
 * EFI_CHECK_EVENT: UEFI Specification 2.10 Section 7.1.6
 */
typedef EFI_STATUS (EFI_API *EFI_CHECK_EVENT) (
    IN EFI_EVENT    Event
);

/**
 * EFI_TIMER_DELAY: UEFI Specification 2.10 Section 7.1.7
 */
typedef enum {
    TimerCancel,
    TimerPeriodic,
    TimerRelative
} EFI_TIMER_DELAY;

/**
 * EFI_SET_TIMER: UEFI Specification 2.10 Section 7.1.7
 */
typedef EFI_STATUS (EFI_API *EFI_SET_TIMER) (
    IN EFI_EVENT        Event,
    IN EFI_TIMER_DELAY  Type,
    IN UINT64           TriggerTime
);

/**
 * EFI_RAISE_TPL: UEFI Specification 2.10 Section 7.1.8
 */
typedef EFI_TPL (EFI_API *EFI_RAISE_TPL) (
    IN EFI_TPL  NewTpl
);

/**
 * EFI_RESTORE_TPL: UEFI Specification 2.10 Section 7.1.9
 */
typedef VOID (EFI_API *EFI_RESTORE_TPL) (
    IN EFI_TPL OldTpl
);

/**
 * EFI_ALLOCATE_TYPE: UEFI Specification 2.10 Section 7.2.1
 */
typedef enum {
    AllocateAnyPages,
    AllocateMaxAddress,
    AllocateAddress,
    MaxAllocateType
} EFI_ALLOCATE_TYPE;

/**
 * EFI_MEMORY_TYPE: UEFI Specification 2.10 Section 7.2.1
 */
typedef enum {
    EfiReservedMemoryType,
    EfiLoaderCode,
    EfiLoaderData,
    EfiBootServicesCode,
    EfiBootServicesData,
    EfiRuntimeServicesCode,
    EfiRuntimeServicesData,
    EfiConventionalMemory,
    EfiUnusableMemory,
    EfiACPIReclaimMemory,
    EfiACPIMemoryNVS,
    EfiMemoryMappedIO,
    EfiMemoryMappedIOPortSpace,
    EfiPalCode,
    EfiPersistentMemory,
    EfiUnacceptedMemoryType,
    EfiMaxMemoryType
} EFI_MEMORY_TYPE;

/**
 * EFI_PHYSICAL_ADDRESS: UEFI Specification 2.10 Section 7.2.1
 */
typedef UINT64 EFI_PHYSICAL_ADDRESS;

/**
 * EFI_ALLOCATE_PAGES: UEFI Specification 2.10 Section 7.2.1
 */
typedef EFI_STATUS (EFI_API *EFI_ALLOCATE_PAGES) (
    IN EFI_ALLOCATE_TYPE        Type,
    IN EFI_MEMORY_TYPE          MemoryType,
    IN UINTN                    Pages,
    IN OUT EFI_PHYSICAL_ADDRESS *Memory
);

/**
 * EFI_FREE_PAGES: UEFI Specification 2.10 Section 7.2.2
 */
typedef EFI_STATUS (EFI_API *EFI_FREE_PAGES) (
    IN EFI_PHYSICAL_ADDRESS Memory,
    IN UINTN                Pages
);

/**
 * EFI_VIRTUAL_ADDRESS: UEFI Specification 2.10 Section 7.2.3
 */
typedef UINT64 EFI_VIRTUAL_ADDRESS;

/**
 * EFI_FREE_PAGES: UEFI Specification 2.10 Section 7.2.3
 */
typedef struct {
    UINT32                  Type;
    EFI_PHYSICAL_ADDRESS    PhysicalStart;
    EFI_VIRTUAL_ADDRESS     VirtualStart;
    UINT64                  NumberOfPages;
    UINT64                  Attribute;
} EFI_MEMORY_DESCRIPTOR;

/**
 * EFI_GET_MEMORY_MAP: UEFI Specification 2.10 Section 7.2.3
 */
typedef EFI_STATUS (EFI_API *EFI_GET_MEMORY_MAP) (
    IN OUT UINTN                *MemoryMapSize,
    OUT EFI_MEMORY_DESCRIPTOR   *MemoryMap,
    OUT UINTN                   *MapKey,
    OUT UINTN                   *DescriptorSize,
    OUT UINT32                  *DescriptorVersion
);

/**
 * EFI_ALLOCATE_POOL: UEFI Specification 2.10 Section 7.2.4
 */
typedef EFI_STATUS (EFI_API *EFI_ALLOCATE_POOL) (
    IN EFI_MEMORY_TYPE  PoolType,
    IN UINTN            Size,
    OUT VOID            **Buffer
);

/**
 * EFI_FREE_POOL: UEFI Specification 2.10 Section 7.2.5
 */
typedef EFI_STATUS (EFI_API *EFI_FREE_POOL) (
    IN VOID *Buffer
);

/**
 * EFI_INTERFACE_TYPE: UEFI Specification 2.10 Section 7.3.2
 */
typedef enum {
    EFI_NATIVE_INTERFACE
} EFI_INTERFACE_TYPE;

/**
 * EFI_INSTALL_PROTOCOL_INTERFACE: UEFI Specification 2.10 Section 7.3.2
 */
typedef EFI_STATUS (EFI_API *EFI_INSTALL_PROTOCOL_INTERFACE) (
    IN OUT EFI_HANDLE       *Handle,
    IN EFI_GUID             *Protocol,
    IN EFI_INTERFACE_TYPE   InterfaceType,
    IN VOID                 *Interface
);

/**
 * EFI_UNINSTALL_PROTOCOL_INTERFACE: UEFI Specification 2.10 Section 7.3.3
 */
typedef EFI_STATUS (EFI_API *EFI_UNINSTALL_PROTOCOL_INTERFACE) (
    IN EFI_HANDLE   Handle,
    IN EFI_GUID     *Protocol,
    IN VOID         *Interface
);

/**
 * EFI_REINSTALL_PROTOCOL_INTERFACE: UEFI Specification 2.10 Section 7.3.4
 */
typedef EFI_STATUS (EFI_API *EFI_REINSTALL_PROTOCOL_INTERFACE) (
    IN EFI_HANDLE   Handle,
    IN EFI_GUID     *Protocol,
    IN VOID         *OldInterface,
    IN VOID         *NewInterface
);

/**
 * EFI_REGISTER_PROTOCOL_NOTIFY: UEFI Specification 2.10 Section 7.3.5
 */
typedef EFI_STATUS (EFI_API *EFI_REGISTER_PROTOCOL_NOTIFY) (
    IN EFI_GUID     *Protocol,
    IN EFI_EVENT    Event,
    OUT VOID        **Registration
);

/**
 * EFI_LOCATE_SEARCH_TYPE: UEFI Specification 2.10 Section 7.3.6
 */
typedef enum {
    AllHandles,
    ByRegisterNotify,
    ByProtocol
} EFI_LOCATE_SEARCH_TYPE;

/**
 * EFI_LOCATE_HANDLE: UEFI Specification 2.10 Section 7.3.6
 */
typedef EFI_STATUS (EFI_API *EFI_LOCATE_HANDLE) (
    IN EFI_LOCATE_SEARCH_TYPE   SearchType,
    IN EFI_GUID                 *Protocol OPTIONAL,
    IN VOID                     *SearchKey OPTIONAL,
    IN OUT UINTN                *BufferSize,
    OUT EFI_HANDLE              *Buffer
);

/**
 * EFI_HANDLE_PROTOCOL: UEFI Specification 2.10 Section 7.3.7
 */
typedef EFI_STATUS (EFI_API *EFI_HANDLE_PROTOCOL) (
    IN EFI_HANDLE   Handle,
    IN EFI_GUID     *Protocol,
    OUT VOID        **Interface
);

/**
 * EFI_DEVICE_PATH_PROTOCOL: UEFI Specification 2.10 Section 10.2
 */
typedef struct {
    UINT8   Type;
    UINT8   SubType;
    UINT16  Length;
    UINT8   Data[];
} EFI_DEVICE_PATH_PROTOCOL;

/**
 * EFI_LOCATE_DEVICE_PATH: UEFI Specification 2.10 Section 7.3.8
 */
typedef EFI_STATUS (EFI_API *EFI_LOCATE_DEVICE_PATH) (
    IN EFI_GUID                     *Protocol,
    IN OUT EFI_DEVICE_PATH_PROTOCOL **DevicePath,
    OUT EFI_HANDLE                  *Device
);

/**
 * EFI_OPEN_PROTOCOL: UEFI Specification 2.10 Section 7.3.9
 */
typedef EFI_STATUS (EFI_API *EFI_OPEN_PROTOCOL) (
    IN EFI_HANDLE   Handle,
    IN EFI_GUID     *Protocol,
    OUT VOID        **Interface OPTIONAL,
    IN EFI_HANDLE   AgentHandle,
    IN EFI_HANDLE   ControllerHandle,
    IN UINT32       Attributes
);

/**
 * EFI_CLOSE_PROTOCOL: UEFI Specification 2.10 Section 7.3.10
 */
typedef EFI_STATUS (EFI_API *EFI_CLOSE_PROTOCOL) (
    IN EFI_HANDLE   Handle,
    IN EFI_GUID     *Protocol,
    IN EFI_HANDLE   AgentHandle,
    IN EFI_HANDLE   ControllerHandle
);

/**
 * EFI_OPEN_PROTOCOL_INFORMATION_ENTRY: UEFI Specification 2.10 Section 7.3.11
 */
typedef struct {
    EFI_HANDLE  AgentHandle;
    EFI_HANDLE  ControllerHandle;
    UINT32      Attributes;
    UINT32      OpenCount;
} EFI_OPEN_PROTOCOL_INFORMATION_ENTRY;

/**
 * EFI_OPEN_PROTOCOL_INFORMATION: UEFI Specification 2.10 Section 7.3.11
 */
typedef EFI_STATUS (EFI_API *EFI_OPEN_PROTOCOL_INFORMATION) (
    IN EFI_HANDLE                               Handle,
    IN EFI_GUID                                 *Protocol,
    OUT EFI_OPEN_PROTOCOL_INFORMATION_ENTRY     **EntryBuffer,
    OUT UINTN                                   *EntryCount
);

/**
 * EFI_CONNECT_CONTROLLER: UEFI Specification 2.10 Section 7.3.12
 */
typedef EFI_STATUS (EFI_API *EFI_CONNECT_CONTROLLER) (
    IN EFI_HANDLE               ControllerHandle,
    IN EFI_HANDLE               *DriverImageHandle OPTIONAL,
    IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL,
    IN BOOLEAN                  Recursive
);

/**
 * EFI_DISCONNECT_CONTROLLER: UEFI Specification 2.10 Section 7.3.13
 */
typedef EFI_STATUS (EFI_API *EFI_DISCONNECT_CONTROLLER) (
    IN EFI_HANDLE   ControllerHandle,
    IN EFI_HANDLE   DriverImageHandle OPTIONAL,
    IN EFI_HANDLE   ChildHandle OPTIONAL
);

/**
 * EFI_PROTOCOLS_PER_HANDLE: UEFI Specification 2.10 Section 7.3.14
 */
typedef EFI_STATUS (EFI_API *EFI_PROTOCOLS_PER_HANDLE) (
    IN EFI_HANDLE   Handle,
    OUT EFI_GUID    ***ProtocolBuffer,
    OUT UINTN       *ProtocolBufferCount
);

/**
 * EFI_LOCATE_HANDLE_BUFFER: UEFI Specification 2.10 Section 7.3.15
 */
typedef EFI_STATUS (EFI_API *EFI_LOCATE_HANDLE_BUFFER) (
    IN EFI_LOCATE_SEARCH_TYPE   SearchType,
    IN EFI_GUID                 *Protocol OPTIONAL,
    IN VOID                     *SearchKey OPTIONAL,
    OUT UINTN                   *NoHandles,
    OUT EFI_HANDLE              **Buffer
);

/**
 * EFI_LOCATE_PROTOCOL: UEFI Specification 2.10 Section 7.3.16
 */
typedef EFI_STATUS (EFI_API *EFI_LOCATE_PROTOCOL) (
    IN EFI_GUID *Protocol,
    IN VOID     *Registration OPTIONAL,
    OUT VOID    **Interface
);

/**
 * EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES: UEFI Specification 2.10 Section 7.3.17
 */
typedef EFI_STATUS (EFI_API *EFI_INSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
    IN OUT EFI_HANDLE   *Handle,
    ...
);

/**
 * EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES: UEFI Specification 2.10 Section 7.3.18
 */
typedef EFI_STATUS (EFI_API *EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES) (
    IN EFI_HANDLE Handle,
    ...
);

/**
 * EFI_IMAGE_LOAD: UEFI Specification 2.10 Section 7.4.1
 */
typedef EFI_STATUS (EFI_API *EFI_IMAGE_LOAD) (
    IN BOOLEAN                  BootPolicy,
    IN EFI_HANDLE               ParentImageHandle,
    IN EFI_DEVICE_PATH_PROTOCOL *DevicePath OPTIONAL,
    IN VOID                     *SourceBuffer OPTIONAL,
    IN UINTN                    SourceSize,
    OUT EFI_HANDLE              *ImageHandle
);

/**
 * EFI_IMAGE_START: UEFI Specification 2.10 Section 7.4.2
 */
typedef EFI_STATUS (EFI_API *EFI_IMAGE_START) (
    IN EFI_HANDLE   ImageHandle,
    OUT UINTN       *ExitDataSize,
    OUT CHAR16      **ExitData OPTIONAL
);

/**
 * EFI_IMAGE_UNLOAD: UEFI Specification 2.10 Section 7.4.3 / 9.1.2
 */
typedef EFI_STATUS (EFI_API *EFI_IMAGE_UNLOAD) (
    IN EFI_HANDLE   ImageHandle
);

/**
 * EFI_IMAGE_ENTRY_POINT: UEFI Specification 2.10 Section 4.1.1 / Section 7.4.4
 */
typedef EFI_STATUS (EFI_API *EFI_IMAGE_ENTRY_POINT) (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
);

/**
 * EFI_EXIT: UEFI Specification 2.10 Section 7.4.5
 */
typedef EFI_STATUS (EFI_API *EFI_EXIT) (
    IN EFI_HANDLE   ImageHandle,
    IN EFI_STATUS   ExitStatus,
    IN UINTN        ExitDataSize,
    IN CHAR16       *ExitData OPTIONAL
);

/**
 * EFI_EXIT_BOOT_SERVICES: UEFI Specification 2.10 Section 7.4.6
 */
typedef EFI_STATUS (EFI_API *EFI_EXIT_BOOT_SERVICES) (
    IN EFI_HANDLE   ImageHandle,
    IN UINTN        MapKey
);

/**
 * EFI_SET_WATCHDOG_TIMER: UEFI Specification 2.10 Section 7.5.1
 */
typedef EFI_STATUS (EFI_API *EFI_SET_WATCHDOG_TIMER) (
    IN UINTN    Timeout,
    IN UINT64   WatchdogCode,
    IN UINTN    DataSize,
    IN CHAR16   *WatchdogData OPTIONAL
);

/**
 * EFI_STALL: UEFI Specification 2.10 Section 7.5.2
 */
typedef EFI_STATUS (EFI_API *EFI_STALL) (
    IN UINTN    Microseconds
);

/**
 * EFI_COPY_MEM: UEFI Specification 2.10 Section 7.5.3
 */
typedef VOID (EFI_API *EFI_COPY_MEM) (
    IN VOID     *Destination,
    IN VOID     *Source,
    IN UINTN    Length
);

/**
 * EFI_SET_MEM: UEFI Specification 2.10 Section 7.5.4
 */
typedef VOID (EFI_API *EFI_SET_MEM) (
    IN VOID     *Buffer,
    IN UINTN    Size,
    IN UINT8    Value
);

/**
 * EFI_GET_NEXT_MONOTONIC_COUNT: UEFI Specification 2.10 Section 7.5.5
 */
typedef EFI_STATUS (EFI_API *EFI_GET_NEXT_MONOTONIC_COUNT) (
    OUT UINT64  *Count
);

/**
 * EFI_INSTALL_CONFIGURATION_TABLE: UEFI Specification 2.10 Section 7.5.6
 */
typedef EFI_STATUS (EFI_API *EFI_INSTALL_CONFIGURATION_TABLE) (
    IN EFI_GUID *Guid,
    IN VOID     *Table
);

/**
 * EFI_CALCULATE_CRC32: UEFI Specification 2.10 Section 7.5.7
 */
typedef EFI_STATUS (EFI_API *EFI_CALCULATE_CRC32) (
    IN VOID     *Data,
    IN UINTN    DataSize,
    OUT UINT32  *Crc32
);

/**
 * EFI_GET_VARIABLE: UEFI Specification 2.10 Section 8.2.1
 */
typedef EFI_STATUS (EFI_API *EFI_GET_VARIABLE) (
    IN CHAR16       *VariableName,
    IN EFI_GUID     *VendorGuid,
    OUT UINT32      *Attributes OPTIONAL,
    IN OUT UINTN    *DataSize,
    OUT VOID        *Data OPTIONAL
 );

/**
 * EFI_GET_NEXT_VARIABLE_NAME: UEFI Specification 2.10 Section 8.2.2
 */
typedef EFI_STATUS (EFI_API *EFI_GET_NEXT_VARIABLE_NAME) (
    IN OUT UINTN    *VariableNameSize,
    IN OUT CHAR16   *VariableName,
    IN OUT EFI_GUID *VendorGuid
 );

/**
 * EFI_SET_VARIABLE: UEFI Specification 2.10 Section 8.2.3
 */
typedef EFI_STATUS (EFI_API *EFI_SET_VARIABLE) (
    IN CHAR16   *VariableName,
    IN EFI_GUID *VendorGuid,
    IN UINT32   Attributes,
    IN UINTN    DataSize,
    IN VOID     *Data
);

/**
 * EFI_SET_VARIABLE: UEFI Specification 2.10 Section 8.2.4
 */
typedef EFI_STATUS (EFI_API *EFI_QUERY_VARIABLE_INFO) (
    IN UINT32   Attributes,
    OUT UINT64  *MaximumVariableStorageSize,
    OUT UINT64  *RemainingVariableStorageSize,
    OUT UINT64  *MaximumVariableSize
);

/**
 * EFI_TIME: UEFI Specification 2.10 Section 8.3.1
 */
typedef struct {
    UINT16  Year;
    UINT8   Month;
    UINT8   Day;
    UINT8   Hour;
    UINT8   Minute;
    UINT8   Second;
    UINT8   Pad1;
    UINT32  Nanosecond;
    INT16   TimeZone;
    UINT8   Daylight;
    UINT8   Pad2;
} EFI_TIME;

/**
 * EFI_TIME_CAPABILITIES: UEFI Specification 2.10 Section 8.3.1
 */
typedef struct {
    UINT32  Resolution;
    UINT32  Accuracy;
    BOOLEAN SetsToZero;
} EFI_TIME_CAPABILITIES;

/**
 * EFI_GET_TIME: UEFI Specification 2.10 Section 8.3.1
 */
typedef EFI_STATUS (EFI_API *EFI_GET_TIME) (
    OUT EFI_TIME                *Time,
    OUT EFI_TIME_CAPABILITIES   *Capabilities OPTIONAL
);

/**
 * EFI_SET_TIME: UEFI Specification 2.10 Section 8.3.2
 */
typedef EFI_STATUS (EFI_API *EFI_SET_TIME) (
    IN EFI_TIME *Time
);

/**
 * EFI_GET_WAKEUP_TIME: UEFI Specification 2.10 Section 8.3.3
 */
typedef EFI_STATUS (EFI_API *EFI_GET_WAKEUP_TIME) (
    OUT BOOLEAN     *Enabled,
    OUT BOOLEAN     *Pending,
    OUT EFI_TIME    *Time
);

/**
 * EFI_SET_WAKEUP_TIME: UEFI Specification 2.10 Section 8.3.3
 */
typedef EFI_STATUS (EFI_API *EFI_SET_WAKEUP_TIME) (
    IN BOOLEAN  Enable,
    IN EFI_TIME *Time OPTIONAL
);

/**
 * EFI_SET_VIRTUAL_ADDRESS_MAP: UEFI Specification 2.10 Section 8.4.1
 */
typedef EFI_STATUS (EFI_API *EFI_SET_VIRTUAL_ADDRESS_MAP) (
    IN UINTN                    MemoryMapSize,
    IN UINTN                    DescriptorSize,
    IN UINT32                   DescriptorVersion,
    IN EFI_MEMORY_DESCRIPTOR    *VirtualMap
);

/**
 * EFI_CONVERT_POINTER: UEFI Specification 2.10 Section 8.4.2
 */
typedef EFI_STATUS (EFI_API *EFI_CONVERT_POINTER) (
    IN UINTN    DebugDisposition,
    IN VOID     **Address
);

/**
 * EFI_RESET_SYSTEM: UEFI Specification 2.10 Section 8.5.1
 */
typedef enum {
   EFI_RESET_COLD,
   EFI_RESET_WARM,
   EFI_RESET_SHUTDOWN,
   EFI_RESET_PLATFORM_SPECIFIC
} EFI_RESET_TYPE;

/**
 * EFI_RESET_SYSTEM: UEFI Specification 2.10 Section 8.5.1
 */
typedef VOID (EFI_API *EFI_RESET_SYSTEM) (
    IN EFI_RESET_TYPE   ResetType,
    IN EFI_STATUS       ResetStatus,
    IN UINTN            DataSize,
    IN VOID             *ResetData OPTIONAL
 );

/**
 * EFI_GET_NEXT_HIGH_MONO_COUNT: UEFI Specification 2.10 Section 8.5.2.1
 */
typedef EFI_STATUS (EFI_API *EFI_GET_NEXT_HIGH_MONO_COUNT) (
    OUT UINT32  *HighCount
);

/**
 * EFI_CAPSULE_HEADER: UEFI Specification 2.10 Section 8.5.3.1
 */
typedef struct {
    EFI_GUID    CapsuleGuid;
    UINT32      HeaderSize;
    UINT32      Flags;
    UINT32      CapsuleImageSize;
} EFI_CAPSULE_HEADER;

/**
 * EFI_RESET_SYSTEM: UEFI Specification 2.10 Section 8.5.3.1
 */
typedef EFI_STATUS (EFI_API *EFI_UPDATE_CAPSULE) (
    IN EFI_CAPSULE_HEADER   **CapsuleHeaderArray,
    IN UINTN                CapsuleCount,
    IN EFI_PHYSICAL_ADDRESS ScatterGatherList OPTIONAL
);

/**
 * EFI_QUERY_CAPSULE_CAPABILITIES: UEFI Specification 2.10 Section 8.5.3.4
 */
typedef EFI_STATUS (EFI_API *EFI_QUERY_CAPSULE_CAPABILITIES) (
    IN EFI_CAPSULE_HEADER   **CapsuleHeaderArray,
    IN UINTN                CapsuleCount,
    OUT UINT64              *MaximumCapsuleSize,
    OUT EFI_RESET_TYPE      *ResetType
);

/**
 * EFI_INPUT_RESET_EX: UEFI Specification 2.10 Section 12.2.2
 */
typedef EFI_STATUS (EFI_API *EFI_INPUT_RESET_EX) (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN BOOLEAN                              ExtendedVerification
);

/**
 * EFI_INPUT_KEY: UEFI Specification 2.10 Section 12.3.3
 */
typedef struct {
    UINT16  ScanCode;
    CHAR16  UnicodeChar;
} EFI_INPUT_KEY;

/**
 * EFI_KEY_TOGGLE_STATE: UEFI Specification 2.10 Section 12.2.3
 */
typedef UINT8 EFI_KEY_TOGGLE_STATE;

/**
 * EFI_KEY_DATA: UEFI Specification 2.10 Section 12.2.3
 */
typedef struct {
    UINT32                  KeyShiftState;
    EFI_KEY_TOGGLE_STATE    KeyToggleState;
} EFI_KEY_STATE;

/**
 * EFI_KEY_DATA: UEFI Specification 2.10 Section 12.2.3
 */
typedef struct {
    EFI_INPUT_KEY   Key;
    EFI_KEY_STATE   KeyState;
} EFI_KEY_DATA;

/**
 * EFI_INPUT_READ_KEY_EX: UEFI Specification 2.10 Section 12.2.3
 */
typedef EFI_STATUS (EFI_API *EFI_INPUT_READ_KEY_EX) (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    OUT EFI_KEY_DATA                        *KeyData
);

/**
 * EFI_SET_STATE: UEFI Specification 2.10 Section 12.2.4
 */
typedef EFI_STATUS (EFI_API *EFI_SET_STATE) (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN EFI_KEY_TOGGLE_STATE                 *KeyToggleState
);

/**
 * EFI_KEY_NOTIFY_FUNCTION: UEFI Specification 2.10 Section 12.2.5
 */
typedef EFI_STATUS (EFI_API *EFI_KEY_NOTIFY_FUNCTION) (
    IN EFI_KEY_DATA *KeyData
);

/**
 * EFI_REGISTER_KEYSTROKE_NOTIFY: UEFI Specification 2.10 Section 12.2.5
 */
typedef EFI_STATUS (EFI_API *EFI_REGISTER_KEYSTROKE_NOTIFY) (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN EFI_KEY_DATA                         *KeyData,
    IN EFI_KEY_NOTIFY_FUNCTION              KeyNotificationFunction,
    OUT VOID                                **NotifyHandle
);

/**
 * EFI_UNREGISTER_KEYSTROKE_NOTIFY: UEFI Specification 2.10 Section 12.2.5
 */
typedef EFI_STATUS (EFI_API *EFI_UNREGISTER_KEYSTROKE_NOTIFY) (
    IN EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL    *This,
    IN VOID                                 *NotificationHandle
);

/**
 * EFI_INPUT_RESET: UEFI Specification 2.10 Section 12.3.2
 */
typedef EFI_STATUS (EFI_API *EFI_INPUT_RESET) (
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This,
    IN BOOLEAN                          ExtendedVerification
);

/**
 * EFI_INPUT_READ_KEY: UEFI Specification 2.10 Section 12.3.2
 */
typedef EFI_STATUS (EFI_API *EFI_INPUT_READ_KEY) (
    IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL   *This,
    OUT EFI_INPUT_KEY                   *Key
);

/**
 * EFI_TEXT_RESET: UEFI Specification 2.10 Section 12.4.2
 */
typedef EFI_STATUS (EFI_API *EFI_TEXT_RESET) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
    IN BOOLEAN                          ExtendedVerification
);

/**
 * EFI_TEXT_STRING: UEFI Specification 2.10 Section 12.4.3
 */
typedef EFI_STATUS (EFI_API *EFI_TEXT_STRING) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
    IN CHAR16                           *String
);

/**
 * EFI_TEXT_TEST_STRING: UEFI Specification 2.10 Section 12.4.4
 */
typedef EFI_STATUS (EFI_API *EFI_TEXT_TEST_STRING) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
    IN CHAR16                           *String
);

/**
 * EFI_TEXT_QUERY_MODE: UEFI Specification 2.10 Section 12.4.5
 */
typedef EFI_STATUS (EFI_API *EFI_TEXT_QUERY_MODE) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
    IN UINTN                            ModeNumber,
    OUT UINTN                           *Columns,
    OUT UINTN                           *Rows
);

/**
 * EFI_TEXT_SET_MODE: UEFI Specification 2.10 Section 12.4.6
 */
typedef EFI_STATUS (EFI_API *EFI_TEXT_SET_MODE) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
    IN UINTN                            ModeNumber
);

/**
 * EFI_TEXT_SET_ATTRIBUTE: UEFI Specification 2.10 Section 12.4.7
 */
typedef EFI_STATUS (EFI_API *EFI_TEXT_SET_ATTRIBUTE) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
    IN UINTN                            Attribute
);

/**
 * EFI_TEXT_CLEAR_SCREEN: UEFI Specification 2.10 Section 12.4.8
 */
typedef EFI_STATUS (EFI_API *EFI_TEXT_CLEAR_SCREEN) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This
);

/**
 * EFI_TEXT_SET_CURSOR_POSITION: UEFI Specification 2.10 Section 12.4.9
 */
typedef EFI_STATUS (EFI_API *EFI_TEXT_SET_CURSOR_POSITION) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
    IN UINTN                            Column,
    IN UINTN                            Row
);

/**
 * EFI_TEXT_ENABLE_CURSOR: UEFI Specification 2.10 Section 12.4.10
 */
typedef EFI_STATUS (EFI_API *EFI_TEXT_ENABLE_CURSOR) (
    IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *This,
    IN BOOLEAN                          Visible
);

/**
 * EFI_LOAD_FILE_PROTOCOL: UEFI Specification 2.10 Section 13.1.1
 */
typedef EFI_STATUS (EFI_API *EFI_LOAD_FILE) (
    IN EFI_LOAD_FILE_PROTOCOL   *This,
    IN EFI_DEVICE_PATH_PROTOCOL *FilePath,
    IN BOOLEAN                  BootPolicy,
    IN OUT UINTN                *BufferSize,
    IN VOID                     *Buffer OPTIONAL
);

/**
 * EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME: UEFI Specification 2.10 Section 13.4.2
 */
typedef EFI_STATUS (EFI_API *EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME) (
    IN EFI_SIMPLE_FILE_SYSTEM_PROTOCOL  *This,
    OUT EFI_FILE_PROTOCOL               **Root
);

/**
 * EFI_FILE_OPEN: UEFI Specification 2.10 Section 13.5.2
 */
typedef EFI_STATUS (EFI_API *EFI_FILE_OPEN) (
    IN EFI_FILE_PROTOCOL    *This,
    OUT EFI_FILE_PROTOCOL   **NewHandle,
    IN CHAR16               *FileName,
    IN UINT64               OpenMode,
    IN UINT64               Attributes
);

/**
 * EFI_FILE_CLOSE: UEFI Specification 2.10 Section 13.5.3
 */
typedef EFI_STATUS (EFI_API *EFI_FILE_CLOSE) (
    IN EFI_FILE_PROTOCOL    *This
);

/**
 * EFI_FILE_DELETE: UEFI Specification 2.10 Section 13.5.4
 */
typedef EFI_STATUS (EFI_API *EFI_FILE_DELETE) (
    IN EFI_FILE_PROTOCOL    *This
);

/**
 * EFI_FILE_READ: UEFI Specification 2.10 Section 13.5.5
 */
typedef EFI_STATUS (EFI_API *EFI_FILE_READ) (
    IN EFI_FILE_PROTOCOL    *This,
    IN OUT UINTN            *BufferSize,
    OUT VOID                *Buffer
);

/**
 * EFI_FILE_WRITE: UEFI Specification 2.10 Section 13.5.6
 */
typedef EFI_STATUS (EFI_API *EFI_FILE_WRITE) (
    IN EFI_FILE_PROTOCOL    *This,
    IN OUT UINTN            *BufferSize,
    IN VOID                 *Buffer
);

/**
 * EFI_FILE_IO_TOKEN: UEFI Specification 2.10 Section 13.5.7
 */
typedef struct {
    EFI_EVENT   Event;
    EFI_STATUS  Status;
    UINTN       BufferSize;
    VOID        *Buffer;
} EFI_FILE_IO_TOKEN;

/**
 * EFI_FILE_OPEN_EX: UEFI Specification 2.10 Section 13.5.7
 */
typedef EFI_STATUS (EFI_API *EFI_FILE_OPEN_EX) (
    IN EFI_FILE_PROTOCOL        *This,
    OUT EFI_FILE_PROTOCOL       **NewHandle,
    IN CHAR16                   *FileName,
    IN UINT64                   OpenMode,
    IN UINT64                   Attributes,
    IN OUT EFI_FILE_IO_TOKEN    *Token
);

/**
 * EFI_FILE_READ_EX: UEFI Specification 2.10 Section 13.5.8
 */
typedef EFI_STATUS (EFI_API *EFI_FILE_READ_EX) (
    IN EFI_FILE_PROTOCOL        *This,
    IN OUT EFI_FILE_IO_TOKEN    *Token
);

/**
 * EFI_FILE_WRITE_EX: UEFI Specification 2.10 Section 13.5.9
 */
typedef EFI_STATUS (EFI_API *EFI_FILE_WRITE_EX) (
    IN EFI_FILE_PROTOCOL        *This,
    IN OUT EFI_FILE_IO_TOKEN    *Token
);

/**
 * EFI_FILE_FLUSH_EX: UEFI Specification 2.10 Section 13.5.10
 */
typedef EFI_STATUS (EFI_API *EFI_FILE_FLUSH_EX) (
    IN EFI_FILE_PROTOCOL        *This,
    IN OUT EFI_FILE_IO_TOKEN    *Token
);

/**
 * EFI_FILE_SET_POSITION: UEFI Specification 2.10 Section 13.5.11
 */
typedef EFI_STATUS (EFI_API *EFI_FILE_SET_POSITION) (
    IN EFI_FILE_PROTOCOL    *This,
    IN UINT64               Position
);

/**
 * EFI_FILE_GET_POSITION: UEFI Specification 2.10 Section 13.5.12
 */
typedef EFI_STATUS (EFI_API *EFI_FILE_GET_POSITION) (
    IN EFI_FILE_PROTOCOL                *This,
    OUT UINT64                          *Position
);

/**
 * EFI_FILE_GET_INFO: UEFI Specification 2.10 Section 13.5.13
 */
typedef EFI_STATUS (EFI_API *EFI_FILE_GET_INFO) (
    IN EFI_FILE_PROTOCOL    *This,
    IN EFI_GUID             *InformationType,
    IN OUT UINTN            *BufferSize,
    OUT VOID                *Buffer
);

/**
 * EFI_FILE_SET_INFO: UEFI Specification 2.10 Section 13.5.14
 */
typedef EFI_STATUS (EFI_API *EFI_FILE_SET_INFO) (
    IN EFI_FILE_PROTOCOL                *This,
    IN EFI_GUID                         *InformationType,
    IN UINTN                            BufferSize,
    IN VOID                             *Buffer
);

/**
 * EFI_FILE_FLUSH: UEFI Specification 2.10 Section 13.5.15
 */
typedef EFI_STATUS (EFI_API *EFI_FILE_FLUSH) (
    IN EFI_FILE_PROTOCOL    *This
);

/**
 * EFI_LOAD_OPTION: UEFI Specification 2.10 Section 3.1.3
 */
struct EFI_LOAD_OPTION {
  UINT32                            Attributes;
  UINT16                            FilePathListLength;
  // CHAR16                         Description[];
  // EFI_DEVICE_PATH_PROTOCOL       FilePathList[];
  // UINT8                          OptionalData[];
};

/**
 * EFI_EXPANDED_LOAD_OPTION: Custom
 */
typedef struct {
    UINTN LoadOptionLength;
    UINTN DescriptionLength;
    UINTN FilePathListLength;
    UINTN OptionalDataLength;

    EFI_LOAD_OPTION *LoadOption;
    CHAR16 *Description;
    EFI_DEVICE_PATH_PROTOCOL *FilePathList;
    UINT8 *OptionalData;
} EFI_EXPANDED_LOAD_OPTION;

/**
 * EFI_TABLE_HEADER: UEFI Specification 2.10 Section 4.2.1
 */
struct EFI_TABLE_HEADER {
    UINT64 Signature;
    UINT32 Revision;
    UINT32 HeaderSize;
    UINT32 CRC32;
    UINT32 Reserved;
};

/**
 * EFI_SYSTEM_TABLE: UEFI Specification 2.10 Section 4.3.1
 */
struct EFI_SYSTEM_TABLE {
    EFI_TABLE_HEADER                Header;
    CHAR16                          *FirmwareVendor;
    UINT32                          FirmwareRevision;
    EFI_HANDLE                      ConsoleInHandle;
    EFI_SIMPLE_TEXT_INPUT_PROTOCOL  *ConsoleIn;
    EFI_HANDLE                      ConsoleOutHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConsoleOut;
    EFI_HANDLE                      StandardErrorHandle;
    EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *StandardError;
    EFI_RUNTIME_SERVICES            *RuntimeServices;
    EFI_BOOT_SERVICES               *BootServices;
    UINTN                           NumberOfTableEntries;
    EFI_CONFIGURATION_TABLE         *ConfigurationTable;
};

/**
 * EFI_BOOT_SERVICES: UEFI Specification 2.10 Section 4.4.1
 */
struct EFI_BOOT_SERVICES {
    EFI_TABLE_HEADER Header;

    EFI_RAISE_TPL       RaiseTPL;
    EFI_RESTORE_TPL     RestoreTPL;

    EFI_ALLOCATE_PAGES  AllocatePages;
    EFI_FREE_PAGES      FreePages;
    EFI_GET_MEMORY_MAP  GetMemoryMap;
    EFI_ALLOCATE_POOL   AllocatePool;
    EFI_FREE_POOL       FreePool;

    EFI_CREATE_EVENT    CreateEvent;
    EFI_SET_TIMER       SetTimer;
    EFI_WAIT_FOR_EVENT  WaitForEvent;
    EFI_SIGNAL_EVENT    SignalEvent;
    EFI_CLOSE_EVENT     CloseEvent;
    EFI_CHECK_EVENT     CheckEvent;

    EFI_INSTALL_PROTOCOL_INTERFACE      InstallProtocolInterface;
    EFI_REINSTALL_PROTOCOL_INTERFACE    ReinstallProtocolInterface;
    EFI_UNINSTALL_PROTOCOL_INTERFACE    UninstallProtocolInterface;
    EFI_HANDLE_PROTOCOL                 HandleProtocol;
    VOID*                               Reserved;
    EFI_REGISTER_PROTOCOL_NOTIFY        RegisterProtocolNotify;
    EFI_LOCATE_HANDLE                   LocateHandle;
    EFI_LOCATE_DEVICE_PATH              LocateDevicePath;
    EFI_INSTALL_CONFIGURATION_TABLE     InstallConfigurationTable;

    EFI_IMAGE_LOAD          LoadImage;
    EFI_IMAGE_START         StartImage;
    EFI_EXIT                Exit;
    EFI_IMAGE_UNLOAD        UnloadImage;
    EFI_EXIT_BOOT_SERVICES  ExitBootServices;

    EFI_GET_NEXT_MONOTONIC_COUNT    GetNextMonotonicCount;
    EFI_STALL                       Stall;
    EFI_SET_WATCHDOG_TIMER          SetWatchdogTimer;

    EFI_CONNECT_CONTROLLER      ConnectController;
    EFI_DISCONNECT_CONTROLLER   DisconnectController;

    EFI_OPEN_PROTOCOL               OpenProtocol;
    EFI_CLOSE_PROTOCOL              CloseProtocol;
    EFI_OPEN_PROTOCOL_INFORMATION   OpenProtocolInformation;

    EFI_PROTOCOLS_PER_HANDLE                    ProtocolsPerHandle;
    EFI_LOCATE_HANDLE_BUFFER                    LocateHandleBuffer;
    EFI_LOCATE_PROTOCOL                         LocateProtocol;
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES  InstallMultipleProtocolInterfaces;
    EFI_UNINSTALL_MULTIPLE_PROTOCOL_INTERFACES  UninstallMultipleProtocolInterfaces;

    EFI_CALCULATE_CRC32 CalculateCrc32;

    EFI_COPY_MEM        CopyMem;
    EFI_SET_MEM         SetMem;
    EFI_CREATE_EVENT_EX CreateEventEx;
};

/**
 * EFI_RUNTIME_SERVICES: UEFI Specification 2.10 Section 4.5.1
 */
struct EFI_RUNTIME_SERVICES {
    EFI_TABLE_HEADER Header;

    EFI_GET_TIME        GetTime;
    EFI_SET_TIME        SetTime;
    EFI_GET_WAKEUP_TIME GetWakeupTime;
    EFI_SET_WAKEUP_TIME SetWakeupTime;

    EFI_SET_VIRTUAL_ADDRESS_MAP SetVirtualAddressMap;
    EFI_CONVERT_POINTER         ConvertPointer;

    EFI_GET_VARIABLE            GetVariable;
    EFI_GET_NEXT_VARIABLE_NAME  GetNextVariableName;
    EFI_SET_VARIABLE            SetVariable;

    EFI_GET_NEXT_HIGH_MONO_COUNT    GetNextHighMonotonicCount;
    EFI_RESET_SYSTEM                ResetSystem;

    EFI_UPDATE_CAPSULE              UpdateCapsule;
    EFI_QUERY_CAPSULE_CAPABILITIES  QueryCapsuleCapabilities;

    EFI_QUERY_VARIABLE_INFO QueryVariableInfo;
};

/**
 * EFI_CONFIGURATION_TABLE: UEFI Specification 2.10 Section 4.6.1
 */
struct EFI_CONFIGURATION_TABLE {
    EFI_GUID    VendorGuid;
    VOID        *VendorTable;
};

struct EFI_LOADED_IMAGE_PROTOCOL {
    UINT32              Revision;
    EFI_HANDLE          ParentHandle;
    EFI_SYSTEM_TABLE    *SystemTable;

    EFI_HANDLE                  DeviceHandle;
    EFI_DEVICE_PATH_PROTOCOL    *FilePath;
    VOID                        *Reserved;

    UINT32  LoadOptionsSize;
    VOID    *LoadOptions;

    VOID                *ImageBase;
    UINT64              ImageSize;
    EFI_MEMORY_TYPE     ImageCodeType;
    EFI_MEMORY_TYPE     ImageDataType;
    EFI_IMAGE_UNLOAD    Unload;
};

/**
 * EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL: UEFI Specification 2.10 Section 12.2.1
 */
struct EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL {
    EFI_INPUT_RESET_EX              Reset;
    EFI_INPUT_READ_KEY_EX           ReadKeyStrokeEx;
    EFI_EVENT                       WaitForKeyEx;
    EFI_SET_STATE                   SetState;
    EFI_REGISTER_KEYSTROKE_NOTIFY   RegisterKeyNotify;
    EFI_UNREGISTER_KEYSTROKE_NOTIFY UnregisterKeyNotify;
};

/**
 * EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL: UEFI Specification 2.10 Section 12.3.1
 */
struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
    EFI_INPUT_RESET     Reset;
    EFI_INPUT_READ_KEY  ReadKeyStroke;
    EFI_EVENT           WaitForKey;
};

/**
 * EFI_SIMPLE_TEXT_OUTPUT_MODE: UEFI Specification 2.10 Section 12.4.1
 */
typedef struct {
    INT32   MaxMode;
    INT32   Mode;
    INT32   Attribute;
    INT32   CursorColumn;
    INT32   CursorRow;
    BOOLEAN CursorVisible;
} EFI_SIMPLE_TEXT_OUTPUT_MODE;

/**
 * EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL: UEFI Specification 2.10 Section 12.4.1
 */
struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
    EFI_TEXT_RESET                  Reset;
    EFI_TEXT_STRING                 OutputString;
    EFI_TEXT_TEST_STRING            TestString;
    EFI_TEXT_QUERY_MODE             QueryMode;
    EFI_TEXT_SET_MODE               SetMode;
    EFI_TEXT_SET_ATTRIBUTE          SetAttribute;
    EFI_TEXT_CLEAR_SCREEN           ClearScreen;
    EFI_TEXT_SET_CURSOR_POSITION    SetCursorPosition;
    EFI_TEXT_ENABLE_CURSOR          EnableCursor;
    EFI_SIMPLE_TEXT_OUTPUT_MODE         *Mode;
};

/**
 * EFI_LOAD_FILE_PROTOCOL: UEFI Specification 2.10 Section 13.1.1
 */
struct EFI_LOAD_FILE_PROTOCOL {
    EFI_LOAD_FILE   LoadFile;
};

/**
 * EFI_SIMPLE_FILE_SYSTEM_PROTOCOL: UEFI Specification 2.10 Section 13.4.1
 */
struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
    UINT64                                      Revision;
    EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_OPEN_VOLUME OpenVolume;
};

/**
 * EFI_FILE_PROTOCOL: UEFI Specification 2.10 Section 13.5.1
 */
struct EFI_FILE_PROTOCOL {
    UINT64                  Revision;
    EFI_FILE_OPEN           Open;
    EFI_FILE_CLOSE          Close;
    EFI_FILE_DELETE         Delete;
    EFI_FILE_READ           Read;
    EFI_FILE_WRITE          Write;
    EFI_FILE_GET_POSITION   GetPosition;
    EFI_FILE_SET_POSITION   SetPosition;
    EFI_FILE_GET_INFO       GetInfo;
    EFI_FILE_SET_INFO       SetInfo;
    EFI_FILE_FLUSH          Flush;
    EFI_FILE_OPEN_EX        OpenEx;
    EFI_FILE_READ_EX        ReadEx;
    EFI_FILE_WRITE_EX       WriteEx;
    EFI_FILE_FLUSH_EX       FlushEx;
};

/**
 * EFI_FILE_INFO: UEFI Specification 2.10 Section 13.5.16
 */
struct EFI_FILE_INFO {
    UINT64      Size;
    UINT64      FileSize;
    UINT64      PhysicalSize;
    EFI_TIME    CreateTime;
    EFI_TIME    LastAccessTime;
    EFI_TIME    ModificationTime;
    UINT64      Attribute;
    CHAR16      FileName [];
};

/**
 * EFI_FILE_SYSTEM_INFO: UEFI Specification 2.10 Section 13.5.17
 */
struct EFI_FILE_SYSTEM_INFO {
    UINT64  Size;
    BOOLEAN ReadOnly;
    UINT64  VolumeSize;
    UINT64  FreeSpace;
    UINT32  BlockSize;
    CHAR16  VolumeLabel [];
};

/**
 * EFI_FILE_SYSTEM_VOLUME_LABEL: UEFI Specification 2.10 Section 13.5.18
 */
struct EFI_FILE_SYSTEM_VOLUME_LABEL {
    // CHAR16  VolumeLabel [];
    CHAR16  VolumeLabel [1];
};

/**
 * Common Type Enumerations: UEFI Specification 2.10 Section 2.3.1
 */
enum {
    FALSE = 0,
    TRUE = 1
};

/**
 * EFI_TPL Enumeration: UEFI Specification 2.10 Section 7.1.8
 */
enum {
    TPL_APPLICATION = 4,
    TPL_CALLBACK = 8,
    TPL_NOTIFY = 16,
    TPL_HIGH_LEVEL = 31,
};

/**
 * EFI_OPEN_PROTOCOL: UEFI Specification 2.10 Section 7.3.9
 */
enum {
    EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL = 0x00000001,
    EFI_OPEN_PROTOCOL_GET_PROTOCOL = 0x00000002,
    EFI_OPEN_PROTOCOL_TEST_PROTOCOL = 0x00000004,
    EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER = 0x00000008,
    EFI_OPEN_PROTOCOL_BY_DRIVER = 0x00000010,
    EFI_OPEN_PROTOCOL_EXCLUSIVE = 0x00000020
};

/**
 * EFI_DEVICE_PATH_PROTOCOL Types: UEFI Specification 2.10 Section 10.3.1
 */
enum {
    EFI_DEVICE_PATH_HARDWARE = 0x01,
    EFI_DEVICE_PATH_ACPI = 0x02,
    EFI_DEVICE_PATH_MESSAGING = 0x03,
    EFI_DEVICE_PATH_MEDIA = 0x04,
    EFI_DEVICE_PATH_BIOS = 0x05,
    EFI_DEVICE_PATH_END = 0x7F
};

/**
 * EFI_DEVICE_PATH_PROTOCOL Media SubTypes: UEFI Specification 2.10 Section 10.3.5
 */
enum {
    EFI_DEVICE_PATH_MEDIA_HARD_DRIVE = 0x01,
    EFI_DEVICE_PATH_MEDIA_CD_ROM = 0x02,
    EFI_DEVICE_PATH_MEDIA_VENDOR = 0x03,
    EFI_DEVICE_PATH_MEDIA_FILE_PATH = 0x04,
    EFI_DEVICE_PATH_MEDIA_PROTOCOL = 0x05,
    EFI_DEVICE_PATH_MEDIA_PIWG_FILE = 0x06,
    EFI_DEVICE_PATH_MEDIA_PIWG_VOLUME = 0x07,
    EFI_DEVICE_PATH_MEDIA_RELATIVE_OFFSET_RANGE = 0x08,
    EFI_DEVICE_PATH_MEDIA_RAM = 0x09
};

/**
 * EFI_TEXT_ATTRIBUTE: UEFI Specification 2.10 Section 12.4.7
 */
enum {
    EFI_BLACK = 0x00,
    EFI_BLUE = 0x01,
    EFI_GREEN = 0x02,
    EFI_CYAN = 0x03,
    EFI_RED = 0x04,
    EFI_MAGENTA = 0x05,
    EFI_BROWN = 0x06,
    EFI_LIGHTGRAY = 0x07,
    EFI_BRIGHT = 0x08,
    EFI_DARKGRAY = (EFI_BLACK | EFI_BRIGHT),
    EFI_LIGHTBLUE = (EFI_BLUE | EFI_BRIGHT),
    EFI_LIGHTGREEN = (EFI_GREEN | EFI_BRIGHT),
    EFI_LIGHTCYAN = (EFI_CYAN | EFI_BRIGHT),
    EFI_LIGHTRED = (EFI_RED | EFI_BRIGHT),
    EFI_LIGHTMAGENTA = (EFI_MAGENTA | EFI_BRIGHT),
    EFI_YELLOW = (EFI_BROWN | EFI_BRIGHT),
    EFI_WHITE = (EFI_LIGHTGRAY | EFI_BRIGHT),
};

/**
 * EFI_TEXT_ATTRIBUTE: UEFI Specification 2.10 Section 12.4.7
 */
#define EFI_TEXT_ATTRIBUTE(Foreground,Background) ((Foreground) | ((Background) << 4))

/**
 * EFI_FILE_OPEN_MODE: UEFI Specification 2.10 Section 12.5.2
 */
#define EFI_FILE_MODE_READ       0x0000000000000001UL
#define EFI_FILE_MODE_WRITE      0x0000000000000002UL
#define EFI_FILE_MODE_CREATE     0x8000000000000000UL
/**
 * EFI_FILE_ATTRIBUTE: UEFI Specification 2.10 Section 12.5.2
 */
#define EFI_FILE_READ_ONLY       0x0000000000000001
#define EFI_FILE_HIDDEN          0x0000000000000002
#define EFI_FILE_SYSTEM          0x0000000000000004
#define EFI_FILE_RESERVED        0x0000000000000008
#define EFI_FILE_DIRECTORY       0x0000000000000010
#define EFI_FILE_ARCHIVE         0x0000000000000020
#define EFI_FILE_VALID_ATTR      0x0000000000000037

/**
 * EFI Scan Codes: UEFI Specification 2.10 Appendix B
 */
enum {
    SCANCODE_NULL = 0x00,
    SCANCODE_UP_ARROW = 0x01,
    SCANCODE_DOWN_ARROW = 0x02,
    SCANCODE_RIGHT_ARROW = 0x03,
    SCANCODE_LEFT_ARROW = 0x04,
    SCANCODE_HOME = 0x05,
    SCANCODE_END = 0x06,
    SCANCODE_INSERT = 0x07,
    SCANCODE_DELETE = 0x08,
    SCANCODE_PAGE_UP = 0x09,
    SCANCODE_PAGE_DOWN = 0x0A,
    SCANCODE_FUNCTION1 = 0x0B,
    SCANCODE_FUNCTION2 = 0x0C,
    SCANCODE_FUNCTION3 = 0x0D,
    SCANCODE_FUNCTION4 = 0x0E,
    SCANCODE_FUNCTION5 = 0x0F,
    SCANCODE_FUNCTION6 = 0x10,
    SCANCODE_FUNCTION7 = 0x11,
    SCANCODE_FUNCTION8 = 0x12,
    SCANCODE_FUNCTION9 = 0x13,
    SCANCODE_FUNCTION10 = 0x14,
    SCANCODE_FUNCTION11 = 0x15,
    SCANCODE_FUNCTION12 = 0x16,
    SCANCODE_ESCAPE = 0x17,
};

/**
 * EFI_STATUS Codes: UEFI Specification 2.10 Appendix D
 */
enum {
    EFI_SUCCESS = 0,
    EFI_LOAD_ERROR = 1,
    EFI_INVALID_PARAMETER = 2,
    EFI_UNSUPPORTED = 3,
    EFI_BAD_BUFFER_SIZE = 4,
    EFI_BUFFER_TOO_SMALL = 5,
    EFI_NOT_READY = 6,
    EFI_DEVICE_ERROR = 7,
    EFI_WRITE_PROTECTED = 8,
    EFI_OUT_OF_RESOURCES = 9,
    EFI_VOLUME_CORRUPTED = 10,
    EFI_VOLUME_FULL = 11,
    EFI_NO_MEDIA = 12,
    EFI_MEDIA_CHANGED = 13,
    EFI_NOT_FOUND = 14,
    EFI_ACCESS_DENIED = 15,
    EFI_NO_RESPONSE = 16,
    EFI_NO_MAPPING = 17,
    EFI_TIMEOUT = 18,
    EFI_NOT_STARTED = 19,
    EFI_ALREADY_STARTED = 20,
    EFI_ABORTED = 21,
    EFI_ICMP_ERROR = 22,
    EFI_TFTP_ERROR = 23,
    EFI_PROTOCOL_ERROR = 24,
    EFI_INCOMPATIBLE_VERSION = 25,
    EFI_SECURITY_VIOLATION = 26,
    EFI_CRC_ERROR = 27,
    EFI_END_OF_MEDIA = 28,
    EFI_END_OF_FILE = 31,
    EFI_INVALID_LANGUAGE = 32,
    EFI_COMPROMISED_DATA = 33,
    EFI_IP_ADDRESS_CONFLICT = 34,
    EFI_HTTP_ERROR = 35,
};

/**
 * EFI_STATUS Warning Codes: UEFI Specification 2.10 Appendix D
 */
enum {
    EFI_WARN_UNKNOWN_GLYPH = 1,
    EFI_WARN_DELETE_FAILURE = 2,
    EFI_WARN_WRITE_FAILURE = 3,
    EFI_WARN_BUFFER_TOO_SMALL = 4,
    EFI_WARN_STALE_DATA = 5,
    EFI_WARN_FILE_SYSTEM = 6,
    EFI_WARN_RESET_REQUIRED = 7,
};

/**
 * EFI_GLOBAL_VARIABLE_GUID: UEFI Specification 2.10 Section 3.3
 */
static EFI_GUID EFI_GLOBAL_VARIABLE_GUID = { 0x8BE4DF61, 0x93CA, 0x11d2, 0xAA, 0x0D, { 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C } };

/**
 * EFI_LOADED_IMAGE_PROTOCOL_GUID: UEFI Specification 2.10 Section 9.1.1
 */
static EFI_GUID EFI_LOADED_IMAGE_PROTOCOL_GUID = { 0x5B1B31A1, 0x9562, 0x11d2, 0x8E, 0x3F, { 0x00, 0xA0, 0xC9, 0x69, 0x72, 0x3B } };

/**
 * EFI_DEVICE_PATH_PROTOCOL_GUID: UEFI Specification 2.10 Section 10.2
 */
static EFI_GUID EFI_DEVICE_PATH_PROTOCOL_GUID = { 0x09576e91, 0x6d3f, 0x11d2, 0x8e, 0x39, { 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } };
/**
 * EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID: UEFI Specification 2.10 Section 13.4.1
 */
static EFI_GUID EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID = { 0x0964e5b22, 0x6459, 0x11d2, 0x8e, 0x39, { 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } };

