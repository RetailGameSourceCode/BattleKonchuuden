ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
ATLAS_DIR=atiki\rsd
ATTOB_DIR=attobi\rsd

all : at.mot at1.mod at2.mod
    psymake

at1.mod: $(ATLAS_DIR)\at1.lz $(ATTOB_DIR)\attobi1.lz
	hdlink /n /l at1.lis

$(ATLAS_DIR)\at1.lz:
	cd $(ATLAS_DIR)
	timpos $(TIM_DIR)/athane.tim  320   0   0 481
	timpos $(TIM_DIR)/hara1.tim   512  80  64 482
	timpos $(TIM_DIR)/hara4.tim   512   0   0 480
	timpos $(TIM_DIR)/hara3.tim   428   0  80 482
	timpos $(TIM_DIR)/syokaku.tim 428 192 128 482
	timpos $(TIM_DIR)/at01.tim    448   0  96 482
	timpos $(TIM_DIR)/hara2.tim   448 144 144 482
	timpos $(TIM_DIR)/me.tim      484   0  32 482
	timpos $(TIM_DIR)/hane2.tim   486 128 112 482
	timpos $(TIM_DIR)/hane1.tim   486 184  48 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	rsdlink atiki.arg
	tmdsort -o at1.tmd a.tmd
	cmplz at1.tmd at1.lz
	del a.tmd
	cd ..\..

$(ATTOB_DIR)\attobi1.lz:
	cd $(ATTOB_DIR)
	timpos $(TIM_DIR)/athane.tim  320   0   0 481
	timpos $(TIM_DIR)/hara1.tim   512  80  64 482
	timpos $(TIM_DIR)/hara4.tim   512   0   0 480
	timpos $(TIM_DIR)/hara3.tim   428   0  80 482
	timpos $(TIM_DIR)/syokaku.tim 428 192 128 482
	timpos $(TIM_DIR)/at01.tim    448   0  96 482
	timpos $(TIM_DIR)/hara2.tim   448 144 144 482
	timpos $(TIM_DIR)/me.tim      484   0  32 482
	timpos $(TIM_DIR)/hane2.tim   486 128 112 482
	timpos $(TIM_DIR)/hane1.tim   486 184  48 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name5.tim      896   0   0 487
	timpos $(NAMEVS)/namevs5.tim  896  16  16 487
	cmplz $(TIM_DIR)/athane.tim  athane.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/at01.tim    at01.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name5.tim      name.lz
	cmplz $(NAMEVS)/namevs5.tim  namevs.lz
	hdlink /n /l ..\..\at1t.lis
	rsdlink attob0.arg
	tmdsort -o attobi1.tmd a.tmd
	cmplz attobi1.tmd attobi1.lz
	del a.tmd
	cd ..\..

at2.mod: $(ATLAS_DIR)\at2.lz $(ATTOB_DIR)\attobi2.lz
	hdlink /n /l at2.lis

$(ATLAS_DIR)\at2.lz:
	cd $(ATLAS_DIR)
	timpos $(TIM_DIR)/athane.tim  576   0   0 489
	timpos $(TIM_DIR)/hara1.tim   768  80  64 490
	timpos $(TIM_DIR)/hara4.tim   768   0   0 488
	timpos $(TIM_DIR)/hara3.tim   684   0  80 490
	timpos $(TIM_DIR)/syokaku.tim 684 192 128 490
	timpos $(TIM_DIR)/at01.tim    704   0  96 490
	timpos $(TIM_DIR)/hara2.tim   704 144 144 490
	timpos $(TIM_DIR)/me.tim      740   0  32 490
	timpos $(TIM_DIR)/hane2.tim   742 128 112 490
	timpos $(TIM_DIR)/hane1.tim   742 184  48 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	rsdlink atiki.arg
	tmdsort -o at2.tmd a.tmd
	cmplz at2.tmd at2.lz
	del a.tmd
	cd ..\..

$(ATTOB_DIR)\attobi2.lz:
	cd $(ATTOB_DIR)
	timpos $(TIM_DIR)/athane.tim  576   0   0 489
	timpos $(TIM_DIR)/hara1.tim   768  80  64 490
	timpos $(TIM_DIR)/hara4.tim   768   0   0 488
	timpos $(TIM_DIR)/hara3.tim   684   0  80 490
	timpos $(TIM_DIR)/syokaku.tim 684 192 128 490
	timpos $(TIM_DIR)/at01.tim    704   0  96 490
	timpos $(TIM_DIR)/hara2.tim   704 144 144 490
	timpos $(TIM_DIR)/me.tim      740   0  32 490
	timpos $(TIM_DIR)/hane2.tim   742 128 112 490
	timpos $(TIM_DIR)/hane1.tim   742 184  48 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name5.tim      926   0   0 495
	timpos $(NAMEVS)/namevs5.tim  896  56  16 495
	cmplz $(TIM_DIR)/athane.tim  athane.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/at01.tim    at01.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name5.tim      name.lz
	cmplz $(NAMEVS)/namevs5.tim  namevs.lz
	hdlink /n /l ..\..\at2t.lis
	rsdlink attob0.arg
	tmdsort -o attobi2.tmd a.tmd
	cmplz attobi2.tmd attobi2.lz
	del a.tmd
	cd ..\..

at.mot: $(ATLAS_DIR)\$(ANM_DIR)/atiki.lz \
		$(ATTOB_DIR)\$(ANM_DIR)/attob0.lz \
		$(ATTOB_DIR)\$(ANM_DIR)/attob1.lz
	hdlink /n /l at.lis

$(ATLAS_DIR)\$(ANM_DIR)/atiki.lz:
	cd $(ATLAS_DIR)\$(ANM_DIR)
	bin2mtn atiki
	cmplz atiki.mtn atiki.lz
	cd ..\..

$(ATTOB_DIR)\$(ANM_DIR)/attob0.lz:
	cd $(ATTOB_DIR)\$(ANM_DIR)
	bin2mtn attob0
	cmplz attob0.mtn attob0.lz
	cd ..\..

$(ATTOB_DIR)\$(ANM_DIR)/attob1.lz:
	cd $(ATTOB_DIR)\$(ANM_DIR)
	bin2mtn attob1
	cmplz attob1.mtn attob1.lz
	cd ..\..


