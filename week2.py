
def crc(data, poly):
    m = len(poly)
    bits = ""

    for ch in data:
        bits += format(ord(ch), '08b')

    temp = list(bits + '0' * (m-1))

    n = len(temp)

    for i in range(n-m+1):
        if temp[i] == '1':
            for j in range(m):
                temp[i+j] = str(int(temp[i+j]) ^ int(poly[j]))

    crc = ''.join(temp[-(m-1):])
    codeword = bits + crc

    return crc, codeword


def crc_check(codeword, poly):
    temp = list(codeword)
    m = len(poly)
    n = len(temp)

    for i in range(n-m+1):
        if temp[i] == '1':
            for j in range(m):
                temp[i+j] = str(int(temp[i+j]) ^ int(poly[j]))

    remainder = ''.join(temp[-(m-1):])
    return remainder


data = input("Enter data: ")
poly = input("Enter polynomial: ")

crc_value, codeword = crc(data, poly)

print("CRC value:", crc_value)
print("Codeword:", codeword)

remainder = crc_check(codeword, poly)

print("Receiver remainder:", remainder)

if '1' not in remainder:
    print("No Error Detected")
else:
    print("Error Detected")
