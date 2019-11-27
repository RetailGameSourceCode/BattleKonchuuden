ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
TOIKI_DIR=otiki\rsd
OTTOB_DIR=25tob\rsd

all : ot.mot ot1.mod ot2.mod
    psymake

ot1.mod: $(TOIKI_DIR)\ot1.lz $(OTTOB_DIR)\ottob1.lz
	hdlink /n /l ot1.lis

$(TOIKI_DIR)\ot1.lz:
	cd $(TOIKI_DIR)
	timpos $(TIM_DIR)/ot01.tim    320   0   0 480
	timpos $(TIM_DIR)/othane.tim  320  88   0 483
	timpos $(TIM_DIR)/hara1.tim   384   0  48 482
	timpos $(TIM_DIR)/hara2.tim   384 160  64 482
	timpos $(TIM_DIR)/hane2.tim   420   0  32 482
	timpos $(TIM_DIR)/hara3.tim   422  56 112 482
	timpos $(TIM_DIR)/hara4.tim   448   0   0 481
	timpos $(TIM_DIR)/syokaku.tim 448  80  96 482
	timpos $(TIM_DIR)/hane1.tim   448 136  80 482
	timpos $(TIM_DIR)/otkao.tim   464  80  16 482
	rsdlink otiki.arg
	tmdsort -o ot1.tmd a.tmd
	cmplz ot1.tmd ot1.lz
	del a.tmd
	cd ..\..

$(OTTOB_DIR)\ottob1.lz:
	cd $(OTTOB_DIR)
	timpos $(TIM_DIR)/ot01.tim    320   0   0 480
	timpos $(TIM_DIR)/othane.tim  320  88   0 483
	timpos $(TIM_DIR)/hara1.tim   384   0  48 482
	timpos $(TIM_DIR)/hara2.tim   384 160  64 482
	timpos $(TIM_DIR)/hane2.tim   420   0  32 482
	timpos $(TIM_DIR)/hara3.tim   422  56 112 482
	timpos $(TIM_DIR)/hara4.tim   448   0   0 481
	timpos $(TIM_DIR)/syokaku.tim 448  80  96 482
	timpos $(TIM_DIR)/hane1.tim   448 136  80 482
	timpos $(TIM_DIR)/otkao.tim   464  80  16 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name25.tim     896   0   0 487
	timpos $(NAMEVS)/namevs25.tim 896  16  16 487
	cmplz $(TIM_DIR)/ot01.tim    ot01.lz
	cmplz $(TIM_DIR)/othane.tim  othane.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/otkao.tim   otkao.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name25.tim     name.lz
	cmplz $(NAMEVS)/namevs25.tim namevs.lz
	hdlink /n /l ..\..\ot1t.lis
	rsdlink ottob.arg
	tmdsort -o ottob1.tmd a.tmd
	cmplz ottob1.tmd ottob1.lz
	del a.tmd
	cd ..\..

ot2.mod: $(TOIKI_DIR)\ot2.lz $(OTTOB_DIR)\ottob2.lz
	hdlink /n /l ot2.lis

$(TOIKI_DIR)\ot2.lz:
	cd $(TOIKI_DIR)
	timpos $(TIM_DIR)/ot01.tim    576   0   0 488
	timpos $(TIM_DIR)/othane.tim  576  88   0 491
	timpos $(TIM_DIR)/hara1.tim   640   0  48 490
	timpos $(TIM_DIR)/hara2.tim   640 160  64 490
	timpos $(TIM_DIR)/hane2.tim   676   0  32 490
	timpos $(TIM_DIR)/hara3.tim   678  56 112 490
	timpos $(TIM_DIR)/hara4.tim   704   0   0 489
	timpos $(TIM_DIR)/syokaku.tim 704  80  96 490
	timpos $(TIM_DIR)/hane1.tim   704 136  80 490
	timpos $(TIM_DIR)/otkao.tim   720  80  16 490
	rsdlink otiki.arg
	tmdsort -o ot2.tmd a.tmd
	cmplz ot2.tmd ot2.lz
	del a.tmd
	cd ..\..

$(OTTOB_DIR)\ottob2.lz:
	cd $(OTTOB_DIR)
	timpos $(TIM_DIR)/ot01.tim    576   0   0 488
	timpos $(TIM_DIR)/othane.tim  576  88   0 491
	timpos $(TIM_DIR)/hara1.tim   640   0  48 490
	timpos $(TIM_DIR)/hara2.tim   640 160  64 490
	timpos $(TIM_DIR)/hane2.tim   676   0  32 490
	timpos $(TIM_DIR)/hara3.tim   678  56 112 490
	timpos $(TIM_DIR)/hara4.tim   704   0   0 489
	timpos $(TIM_DIR)/syokaku.tim 704  80  96 490
	timpos $(TIM_DIR)/hane1.tim   704 136  80 490
	timpos $(TIM_DIR)/otkao.tim   720  80  16 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name25.tim     926   0   0 495
	timpos $(NAMEVS)/namevs25.tim 896  56  16 495
	cmplz $(TIM_DIR)/ot01.tim    ot01.lz
	cmplz $(TIM_DIR)/othane.tim  othane.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/otkao.tim   otkao.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name25.tim     name.lz
	cmplz $(NAMEVS)/namevs25.tim namevs.lz
	hdlink /n /l ..\..\ot2t.lis
	rsdlink ottob.arg
	tmdsort -o ottob2.tmd a.tmd
	cmplz ottob2.tmd ottob2.lz
	del a.tmd
	cd ..\..

ot.mot: $(TOIKI_DIR)\$(ANM_DIR)/otiki.lz
	hdlink /n /l ot.lis

$(TOIKI_DIR)\$(ANM_DIR)/otiki.lz:
	cd $(TOIKI_DIR)\$(ANM_DIR)
	bin2mtn otiki
	cmplz otiki.mtn otiki.lz
	cd ..\..

