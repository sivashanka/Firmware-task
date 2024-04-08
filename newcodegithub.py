import serial
import time

siva = serial.Serial('COM8', 2400)

with open('Data.txt', 'rb') as file:
    data_to_send = file.read()
    start_time_transmission = time.time()
    total_bytes_sent = 0
    print("Transmission from PC to UNO Started/n")
    for byte in data_to_send:
        siva.write(bytes([byte]))
        total_bytes_sent += 1
        elapsed_time_transmission = time.time() - start_time_transmission

        if elapsed_time_transmission > 0:
            transmission_speed = total_bytes_sent * 8 / elapsed_time_transmission
            print("Transmission Speed: {:.2f} bits/second".format(transmission_speed))
        else:
            continue

print("\nAll data is transmitted from PC to UNO\n")
time.sleep(2)

siva.write(b"0\n1005\n")

start_time_reception = time.time()
total_bytes_received = 0
reception_time_interval = 1

received_string = ""
print("Receiving data from UNO to PC")

while True:
    if siva.in_waiting > 0:
        received_data = siva.read(siva.in_waiting)
        received_string += received_data.decode()
        total_bytes_received += len(received_data)
        elapsed_time_reception = time.time() - start_time_reception

        if elapsed_time_reception >= reception_time_interval:
            receiving_speed = total_bytes_received * 8 / elapsed_time_reception
            print("Receiving Speed: {:.2f} bits/second".format(receiving_speed))
            total_bytes_received = 0
            start_time_reception = time.time()

    if len(received_string) >= len(data_to_send):
        break

print("\nReceived Data:\n")
print(received_string)
