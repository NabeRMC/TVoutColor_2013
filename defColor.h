#define OutPixel\
        "out 0x08,r18\n\t"\
        "out 0x08,r19\n\t"\
        "out 0x08,r20\n\t"\
        "out 0x08,r21\n\t"\

#define OutP\
        "out 0x08,r18\n\t"\
        "out 0x08,r19\n\t"\
        "out 0x08,r20\n\t"\
        "out 0x08,r21\n\t"\

#define OutB\
        "out 0x08,r23\n\t"\
        "out 0x08,r23\n\t"\
        "out 0x08,r23\n\t"\
        "out 0x08,r23\n\t"\

#define OutBlack\
        "out 0x08,r23\n\t"\
        "out 0x08,r23\n\t"\
        "out 0x08,r23\n\t"\
        "out 0x08,r23\n\t"\

#define OutBurst\
        "out 0x08,r18\n\t"\
        "out 0x08,r19\n\t"\
        "out 0x08,r20\n\t"\
        "out 0x08,r21\n\t"\
        
#define SetColRed\
        "ldi r18,24\n\t"\
        "ldi r19,10\n\t"\
        "ldi r20,2\n\t"\
        "ldi r21,16\n\t"\
        
#define SetColGrn\
        "ldi r18,9\n\t"\
        "ldi r19,13\n\t"\
        "ldi r20,27\n\t"\
        "ldi r21,23\n\t"\
        
#define SetColBlu\
        "ldi r18,8\n\t"\
        "ldi r19,18\n\t"\
        "ldi r20,12\n\t"\
        "ldi r21,2\n\t"\
        
#define SetColMag\
        "ldi r18,24\n\t"\
        "ldi r19,20\n\t"\
        "ldi r20,6\n\t"\
        "ldi r21,10\n\t"\
        
#define SetColCyn\
        "ldi r18,9\n\t"\
        "ldi r19,23\n\t"\
        "ldi r20,31\n\t"\
        "ldi r21,17\n\t"\
        
#define SetColYel\
        "ldi r18,25\n\t"\
        "ldi r19,15\n\t"\
        "ldi r20,21\n\t"\
        "ldi r21,31\n\t"\

#define SetColWhi\
        "ldi r18,25\n\t"\
        "ldi r19,25\n\t"\
        "ldi r20,25\n\t"\
        "ldi r21,25\n\t"\
        
#define SetColBlk\
        "ldi r18,7\n\t"\
        "ldi r19,7\n\t"\
        "ldi r20,7\n\t"\
        "ldi r21,7\n\t"\

