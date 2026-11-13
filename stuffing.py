def character_stuffing():
    n=int(input("enter no of frames: "))
    frames=[]
    for i in range(n):
        frame=input("enter frame: ")
        frames.append(frame)
    transmitted=""
    for frame in frames:
        transmitted+=str(len(frame)+1)+frame
    print("transmitted data:",transmitted)

    print("received frames:")
    i=0
    while i<len(transmitted):
        count=int(transmitted[i])
        res=transmitted[i+1:i+count]
        print(res)
        i+=count


def byte_stuffing():
    data=input("enter data: ")
    frame='f'
    for ch in data:
        if ch=='f' or ch=='e':
            frame+='e'
        frame+=ch

    frame+='f'
    print("transmitted frame:",frame)

    print("received data:")
    i=1
    res=""
    while i<len(frame)-1:
        if frame[i]=='e':
            i+=1
        res+=frame[i]
        i+=1
    print(res)


def bit_stuffing():
    data2 = input("Enter binary data: ")

    data=""
    for ch in data2:
        data+= format(int(ch, 16), '04b')

    stuffed = "01111110"
    count = 0

    # Sender side - Bit Stuffing
    for bit in data:
        stuffed += bit

        if bit == '1':
            count += 1
        else:
            count = 0

        if count == 5:
            stuffed += '0'
            count = 0

    stuffed += "01111110"

    print("Transmitted frame:", stuffed)

    # Receiver side - Bit Destuffing
    result = ""
    count = 0
    i = 8

    while i < len(stuffed) - 8:
        bit = stuffed[i]
        result += bit

        if bit == '1':
            count += 1
        else:
            count = 0

        if count == 5:
            i += 1
            count = 0

        i += 1

    print("Received data:", result)


character_stuffing()
byte_stuffing()
bit_stuffing()
