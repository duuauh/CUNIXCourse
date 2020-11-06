import struct

def str2bin(s):
    indice = 0
    strbuf = ''
    binflow = b''
    if((ord(s[0])>=48) & (ord(s[0])<=57)):
        for c in s:
            if c==',':
                if indice==0:
                    binflow = struct.pack('>I', int(strbuf))

                binflow += struct.pack('>b', ord(c))
                indice += 1
                strbuf = ''
            elif c==';':
                binflow += struct.pack('>b', int(strbuf))
                strbuf = ''
            elif indice==0:
                strbuf += c
            elif indice==3:
                strbuf += c
            else:
                binflow += struct.pack('>b', ord(c))
        binflow += struct.pack('>b', ord('\n'))
    else:
        for c in s:
            binflow += struct.pack('>b', ord(c))

    return binflow

def bin2strh(b):
    strbuf = ''
    for item in b:
        strbuf += chr(item)
    return strbuf.strip()


def bin2str(b):
    strbuf = ''
    strbuf += str(struct.unpack('>I', b[0:4])[0])
    indice = 0
    for c in b[4:]:
        #s = str(struct.unpack('>b', c)[0])
        s = chr(c)
        if s==',':
            indice += 1
        strbuf += s
        if indice==3:
            break
    
    strbuf += str(b[-2])
    #print(b[-2])
    strbuf += ';'
    return strbuf