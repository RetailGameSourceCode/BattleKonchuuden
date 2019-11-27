ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
ZO_DIR=zosan\rsd
ZOTOB_DIR=zotob\rsd

all : zo.mot zo1.mod zo2.mod
    psymake

zo1.mod: $(ZO_DIR)\zo1.lz $(ZOTOB_DIR)\zotob1.lz
	hdlink /n /l zo1.lis

$(ZO_DIR)\zo1.lz:
	cd $(ZO_DIR)
	timpos $(TIM_DIR)/body256.tim 320   0   0 481
	timpos $(TIM_DIR)/syokaku.tim 432   0  80 482
	timpos $(TIM_DIR)/hara1.tim   448   0  32 482
	timpos $(TIM_DIR)/hara2.tim   448 160  16 482
	timpos $(TIM_DIR)/muneura.tim 470   0  64 482
	timpos $(TIM_DIR)/mune256.tim 512   0   0 480
	timpos $(TIM_DIR)/me.tim      560  56  48 482
	rsdlink nmlzo.arg
	tmdsort -o zo1.tmd a.tmd
	cmplz zo1.tmd zo1.lz
	del a.tmd
	cd ..\..

$(ZOTOB_DIR)\zotob1.lz:
	cd $(ZOTOB_DIR)
	timpos $(TIM_DIR)/body256.tim 320   0   0 481
	timpos $(TIM_DIR)/syokaku.tim 432   0  80 482
	timpos $(TIM_DIR)/hara4.tim   432  56 128 482
	timpos $(TIM_DIR)/hara1.tim   448   0  32 482
	timpos $(TIM_DIR)/hara2.tim   448 160  16 482
	timpos $(TIM_DIR)/muneura.tim 470   0  64 482
	timpos $(TIM_DIR)/mune256.tim 512   0   0 480
	timpos $(TIM_DIR)/hane2.tim   512 128  96 482
	timpos $(TIM_DIR)/hane1.tim   560   0 112 482
	timpos $(TIM_DIR)/me.tim      560  56  48 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name8.tim      896   0   0 487
	timpos $(NAMEVS)/namevs8.tim  896  16  16 487
	cmplz $(TIM_DIR)/body256.tim body256.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/muneura.tim muneura.lz
	cmplz $(TIM_DIR)/mune256.tim mune256.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name8.tim      name.lz
	cmplz $(NAMEVS)/namevs8.tim  namevs.lz
	hdlink /n /l ..\..\zo1t.lis
	rsdlink zotob.arg
	tmdsort -o zotob1.tmd a.tmd
	cmplz zotob1.tmd zotob1.lz
	del a.tmd
	cd ..\..

zo2.mod: $(ZO_DIR)\zo2.lz $(ZOTOB_DIR)\zotob2.lz
	hdlink /n /l zo2.lis

$(ZO_DIR)\zo2.lz:
	cd $(ZO_DIR)
	timpos $(TIM_DIR)/body256.tim 576   0   0 489
	timpos $(TIM_DIR)/syokaku.tim 688   0  80 490
	timpos $(TIM_DIR)/hara1.tim   704   0  32 490
	timpos $(TIM_DIR)/hara2.tim   704 160  16 490
	timpos $(TIM_DIR)/muneura.tim 726   0  64 490
	timpos $(TIM_DIR)/mune256.tim 768   0   0 488
	timpos $(TIM_DIR)/me.tim      816  56  48 490
	rsdlink nmlzo.arg
	tmdsort -o zo2.tmd a.tmd
	cmplz zo2.tmd zo2.lz
	del a.tmd
	cd ..\..

$(ZOTOB_DIR)\zotob2.lz:
	cd $(ZOTOB_DIR)
	timpos $(TIM_DIR)/body256.tim 576   0   0 489
	timpos $(TIM_DIR)/syokaku.tim 688   0  80 490
	timpos $(TIM_DIR)/hara4.tim   688  56 128 490
	timpos $(TIM_DIR)/hara1.tim   704   0  32 490
	timpos $(TIM_DIR)/hara2.tim   704 160  16 490
	timpos $(TIM_DIR)/muneura.tim 726   0  64 490
	timpos $(TIM_DIR)/mune256.tim 768   0   0 488
	timpos $(TIM_DIR)/hane2.tim   768 128  96 490
	timpos $(TIM_DIR)/hane1.tim   816   0 112 490
	timpos $(TIM_DIR)/me.tim      816  56  48 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name8.tim      926   0   0 495
	timpos $(NAMEVS)/namevs8.tim  896  56  16 495
	cmplz $(TIM_DIR)/body256.tim body256.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/muneura.tim muneura.lz
	cmplz $(TIM_DIR)/mune256.tim mune256.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name8.tim      name.lz
	cmplz $(NAMEVS)/namevs8.tim  namevs.lz
	hdlink /n /l ..\..\zo2t.lis
	rsdlink zotob.arg
	tmdsort -o zotob2.tmd a.tmd
	cmplz zotob2.tmd zotob2.lz
	del a.tmd
	cd ..\..

zo.mot: $(ZO_DIR)\$(ANM_DIR)/zoiki.lz \
		$(ZOTOB_DIR)\$(ANM_DIR)/zotos0.lz \
		$(ZOTOB_DIR)\$(ANM_DIR)/zotos1.lz \
		$(ZOTOB_DIR)\$(ANM_DIR)/zotos2.lz \
		$(ZO_DIR)\$(ANM_DIR)/08cmb0.lz \
		$(ZO_DIR)\$(ANM_DIR)/08cmb0m.lz \
		$(ZO_DIR)\$(ANM_DIR)/08cmb1.lz \
		$(ZO_DIR)\$(ANM_DIR)/08cmb1m.lz \
		$(ZO_DIR)\$(ANM_DIR)/08cmb2.lz \
		$(ZO_DIR)\$(ANM_DIR)/08cmb2m.lz \
		$(ZO_DIR)\$(ANM_DIR)/08nag0.lz \
		$(ZO_DIR)\$(ANM_DIR)/08nag1.lz \
		$(ZO_DIR)\$(ANM_DIR)/08geki1.lz \
		$(ZO_DIR)\$(ANM_DIR)/08geki2.lz
	hdlink /n /l zo.lis

$(ZO_DIR)\$(ANM_DIR)/zoiki.lz:
	cd $(ZO_DIR)\$(ANM_DIR)
	bin2mtn zoiki
	cmplz zoiki.mtn zoiki.lz
	cd ..\..

$(ZOTOB_DIR)\$(ANM_DIR)/zotos0.lz:
	cd $(ZOTOB_DIR)\$(ANM_DIR)
	bin2mtn zotos0
	cmplz zotos0.mtn zotos0.lz
	cd ..\..

$(ZOTOB_DIR)\$(ANM_DIR)/zotos1.lz:
	cd $(ZOTOB_DIR)\$(ANM_DIR)
	bin2mtn zotos1
	cmplz zotos1.mtn zotos1.lz
	cd ..\..

$(ZOTOB_DIR)\$(ANM_DIR)/zotos2.lz:
	cd $(ZOTOB_DIR)\$(ANM_DIR)
	bin2mtn zotos2
	cmplz zotos2.mtn zotos2.lz
	cd ..\..

$(ZO_DIR)\$(ANM_DIR)/08cmb0.lz:
	cd $(ZO_DIR)\$(ANM_DIR)
	bin2mtn 08cmb0
	cmplz 08cmb0.mtn 08cmb0.lz
	cd ..\..

$(ZO_DIR)\$(ANM_DIR)/08cmb0m.lz:
	cd $(ZO_DIR)\$(ANM_DIR)
	bin2mtn 08cmb0m
	cmplz 08cmb0m.mtn 08cmb0m.lz
	cd ..\..

$(ZO_DIR)\$(ANM_DIR)/08cmb1.lz:
	cd $(ZO_DIR)\$(ANM_DIR)
	bin2mtn 08cmb1
	cmplz 08cmb1.mtn 08cmb1.lz
	cd ..\..

$(ZO_DIR)\$(ANM_DIR)/08cmb1m.lz:
	cd $(ZO_DIR)\$(ANM_DIR)
	bin2mtn 08cmb1m
	cmplz 08cmb1m.mtn 08cmb1m.lz
	cd ..\..

$(ZO_DIR)\$(ANM_DIR)/08cmb2.lz:
	cd $(ZO_DIR)\$(ANM_DIR)
	bin2mtn 08cmb2
	cmplz 08cmb2.mtn 08cmb2.lz
	cd ..\..

$(ZO_DIR)\$(ANM_DIR)/08cmb2m.lz:
	cd $(ZO_DIR)\$(ANM_DIR)
	bin2mtn 08cmb2m
	cmplz 08cmb2m.mtn 08cmb2m.lz
	cd ..\..

$(ZO_DIR)\$(ANM_DIR)/08geki1.lz:
	cd $(ZO_DIR)\$(ANM_DIR)
	bin2mtn 08gek1
	cmplz 08gek1.mtn 08geki1.lz
	cd ..\..

$(ZO_DIR)\$(ANM_DIR)/08geki2.lz:
	cd $(ZO_DIR)\$(ANM_DIR)
	bin2mtn 08gek2
	cmplz 08gek2.mtn 08geki2.lz
	cd ..\..

$(ZO_DIR)\$(ANM_DIR)/08nag0.lz:
	cd $(ZO_DIR)\$(ANM_DIR)
	bin2mtn 08nag0
	cmplz 08nag0.mtn 08nag0.lz
	cd ..\..

$(ZO_DIR)\$(ANM_DIR)/08nag1.lz:
	cd $(ZO_DIR)\$(ANM_DIR)
	bin2mtn 08nag1
	cmplz 08nag1.mtn 08nag1.lz
	cd ..\..


