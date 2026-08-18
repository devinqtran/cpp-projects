import socket
import threading
import sys

def listen_to_server(sock):
    while True:
        try:
            # Wait for data from the server
            data = sock.recv(1024)
            if not data:
                print("\n[Disconnected from server]")
                break
            # Print whatever the server sends us
            print(data.decode(), end='')
        except:
            break

try:
    # Connect to the C++ server
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(('localhost', 8080))
    
    # Start a background thread to listen for server messages
    threading.Thread(target=listen_to_server, args=(s,), daemon=True).start()
    
    # The main thread waits for you to type commands
    while True:
        cmd = sys.stdin.readline()
        if not cmd:
            break
        s.send(cmd.encode())

except KeyboardInterrupt:
    print("\nClosing...")
except Exception as e:
    print(f"Connection failed: {e}")