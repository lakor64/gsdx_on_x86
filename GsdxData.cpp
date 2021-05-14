#include "StdAfx.h"
#include "GSDXLoader.h"

#include <array>

static void _irq()
{
	/* GS IRQ */
}

void execGs2(GSDX* g)
{
	/* GS CODE */
	
	GSPrivRegSet regs;
	g->setBaseMem(&regs);
	g->irqCallback(_irq);
	
	// from gsKit
	
	g->reset();
	g->writeCSR(0x0);

	regs.DISP[0].DISPLAY.DX = 0;
	regs.DISP[0].DISPLAY.DY = 0;
	regs.DISP[0].DISPLAY.DW = 800;
	regs.DISP[0].DISPLAY.DH = 600;
	regs.DISP[0].DISPLAY.MAGH = 0;
	regs.DISP[0].DISPLAY.MAGV = 0;


	regs.PMODE.EN1 = 0;
	regs.PMODE.EN2 = 0;
	regs.PMODE.CRTMD = 1;
	regs.PMODE.MMOD = 0;
	regs.PMODE.AMOD = 1;
	regs.PMODE.SLBG = 0;
	regs.PMODE.ALP = 0x80;

	regs.BGCOLOR.R = 0xFF;
	regs.BGCOLOR.G = 0;
	regs.BGCOLOR.B = 0;
	
}
