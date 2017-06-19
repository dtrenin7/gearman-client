import sys
from ctypes import *

gearman_lib = cdll.LoadLibrary("libgearman-client.so")
gearman_call = gearman_lib.gearman_call
gearman_call.argtypes = [c_char_p, c_char_p, c_char_p, c_ulong, c_int, POINTER(c_int)]
gearman_call.restype = c_void_p

gearman_free = gearman_lib.gearman_free
gearman_free.argtypes = [c_void_p]
gearman_free.restype = None

def gearman_client(servers, function, data, delay):
    cservers = c_char_p(servers.encode('utf-8'))
    cfunction = c_char_p(function.encode('utf-8'))
    print(len(data))
    rsize = c_int()
    raw_ptr = gearman_call(cservers, cfunction, c_char_p(data), c_ulong(len(data)), c_int(delay), rsize)
    if rsize.value == 0:
        return None;
    result = bytearray((c_byte * rsize.value).from_address(raw_ptr)).decode('utf-8')
    gearman_free(raw_ptr)
    return result

if __name__ == '__main__':
    try:
        servers = sys.argv[1]
        function = sys.argv[2]
        path = sys.argv[3]
        with open(path,'rb') as input_file:
            data = input_file.read()
            input_file.close()
            print(gearman_client(servers, function, data, 0))
    except IndexError:
        print("USAGE: python3 gearman_client.py servers function input_file")


