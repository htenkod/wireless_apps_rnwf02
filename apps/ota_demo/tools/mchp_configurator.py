import netifaces
import ipaddress
import socket

DEFAULT_OTA_SERVER = "192.168.205.75"
DEFAULT_OTA_PORT   = "8000"
DEFAULT_OTA_IMAGE  = "fw1_june15.bin"


def share_ota_config(socket):
    socket.write()


def check_port(ip_address, port):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        try:
            s.settimeout(.1)  # Set the socket timeout to 1 second
            result = s.connect_ex((ip_address, port))
            if result == 0:
                s.settimeout(5)  # Set the socket timeout to 1 second
                print("\r\n#########Device Found!#########\r\n")                                
                recv_buf = s.recv(512)
                recv_buf = recv_buf.decode('utf-8', 'ignore')                
                dev_info = recv_buf.split(' ')
                # print(dev_info)
                dev_dict = {}
                for info in dev_info:
                    try:                    
                        id, val = info.split(',')
                        dev_dict[id] = val
                    except:
                        continue      

                print('Device ID = ', hex(int(dev_dict['1'])))
                print('Num of Images = ', hex(int(dev_dict['14'])))
                # print('Num of Images = ', hex(int(dev_dict['15.0'])))
                print("\r\n###########################\r\n")  
            
                print(f"Port {port} is open on {ip_address}")                    
                server = input("Enter the Server URL: ")                
                if not server: 
                    server = DEFAULT_OTA_SERVER           
                    print(DEFAULT_OTA_SERVER) 
                port = input("Enter the Server port: ")
                if not port: 
                    port = DEFAULT_OTA_PORT
                    print(DEFAULT_OTA_PORT)
                image = input("Enter the Image Name: ")
                if not image: 
                    image = DEFAULT_OTA_IMAGE
                    print(DEFAULT_OTA_IMAGE)
                
                s.send(f"firmware:{str(port)}, {server}, {image}".encode('utf-8'))
                                                
                
            # else:
            #     print(f"Port {port} is closed on {ip_address}")
        except socket.error as e:
            print(f"Error occurred while checking port {port} on {ip_address}: {str(e)}")

    return result


def mask_ip_address(ip_address, subnet_mask):
    ip_parts = ip_address.split('.')
    subnet_parts = subnet_mask.split('.')

    # Perform bitwise AND operation on each octet
    masked_parts = [str(int(ip_parts[i]) & int(subnet_parts[i])) for i in range(4)]

    masked_ip_address = '.'.join(masked_parts)
    return masked_ip_address

def find_subnet_mask_len(ip_address, subnet):
    network = ipaddress.ip_network(f"{ip_address}/{subnet}", strict=False)
    subnet_mask = str(network.netmask)
    subnet_mask_length = network.prefixlen
    return subnet_mask_length

def iterate_subnet(subnet):
    network = ipaddress.ip_network(subnet)
    for ip_address in network.hosts():
        print(ip_address, end='\r')
        if(check_port(str(ip_address), 6666) == 0):            
            return    
    print("No Device Found!")



def get_interface_info(interface):
    ifaddresses = netifaces.ifaddresses(interface)
    
    # Get IPv4 address information
    if netifaces.AF_INET in ifaddresses:
        ipv4_info = ifaddresses[netifaces.AF_INET][0]
        gateway = ipv4_info.get('broadcast', None)
        subnet_mask = ipv4_info.get('netmask', None)   
        ip_addr = ipv4_info.get('addr', None)     
        
        return gateway, subnet_mask, ip_addr

    return None, None

# Example usage
interface_name = 'en0'  # Replace with your desired interface name

# Get interface information
gateway, subnet_mask, ipAddr = get_interface_info(interface_name)

subnet_count = find_subnet_mask_len(ipAddr, subnet_mask)

print("Looking for Microchip Wi-Fi Devices")

subnet = mask_ip_address(ipAddr, subnet_mask) + '/' + str(subnet_count)

iterate_subnet(subnet)
