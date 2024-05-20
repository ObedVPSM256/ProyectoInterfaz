import serial
import struct

# Configura la conexión serial
ser = serial.Serial('COM6', 115200)  
while True:
    file_size_bytes = ser.read(4)
    file_size = struct.unpack('<I', file_size_bytes)[0]

    # Lee los datos de la fotografía
    image_data = ser.read(file_size)

    # Guarda los datos en un archivo
    file_name = f"photo_{len([f for f in os.listdir('.') if f.startswith('photo_')])}.jpg"
    with open(file_name, 'wb') as f:
        f.write(image_data)

    print(f"Fotografía guardada como {file_name}")