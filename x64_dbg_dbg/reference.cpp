#include "reference.h"
#include "debugger.h"
#include "memory.h"
#include "console.h"

int reffind(uint addr, uint size, CBREF cbRef, void* userinfo, bool silent)
{
    uint start_addr;
    uint start_size;
    uint base;
    uint base_size;
    base=memfindbaseaddr(fdProcessInfo->hProcess, addr, &base_size);
    if(!base or !base_size)
    {
        if(!silent)
            dputs("invalid memory page");
        return 0;
    }
    
    if(!size) //assume the whole page
    {
        start_addr=base;
        start_size=base_size;
    }
    else //custom boundaries
    {
        start_addr=addr;
        uint maxsize=size-(start_addr-base);
        if(size<maxsize) //check if the size fits in the page
            start_size=size;
        else
            start_size=maxsize;
    }
    unsigned char* data=(unsigned char*)emalloc(start_size, "reffind:data");
    if(!memread(fdProcessInfo->hProcess, (const void*)start_addr, data, start_size, 0))
    {
        if(!silent)
            dputs("error reading memory");
        efree(data, "reffind:data");
        return 0;
    }
    DISASM disasm;
    memset(&disasm, 0, sizeof(disasm));
#ifdef _WIN64
    disasm.Archi=64;
#endif // _WIN64
    disasm.EIP=(UIntPtr)data;
    disasm.VirtualAddr=(UInt64)start_addr;
    uint i=0;
    BASIC_INSTRUCTION_INFO basicinfo;
    cbRef(&disasm, &basicinfo, 0); //allow initializing
    REFINFO refinfo;
    memset(&refinfo, 0, sizeof(REFINFO));
    refinfo.userinfo=userinfo;
    while(i<start_size)
    {
        if(!(i%0x1000))
        {
            double percent=(double)i/(double)start_size;
            GuiReferenceSetProgress((int)(percent*100));
        }
        int len=Disasm(&disasm);
        if(len!=UNKNOWN_OPCODE)
        {
            fillbasicinfo(&disasm, &basicinfo);
            if(cbRef(&disasm, &basicinfo, &refinfo))
                refinfo.refcount++;
        }
        else
            len=1;
        disasm.EIP+=len;
        disasm.VirtualAddr+=len;
        i+=len;
    }
    GuiReferenceSetProgress(100);
    GuiReferenceReloadData();
    efree(data, "reffind:data");
    return refinfo.refcount;
}