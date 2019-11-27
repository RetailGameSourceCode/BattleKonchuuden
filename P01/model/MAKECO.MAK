ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
CORCA_DIR=06\rsd
COTOB_DIR=06tob\rsd

all : co.mot co1.mod co2.mod
    psymake

co1.mod: $(CORCA_DIR)\co1.lz $(COTOB_DIR)\cotobi1.lz
	hdlink /n /l co1.lis

$(CORCA_DIR)\co1.lz:
	cd $(CORCA_DIR)
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
	tmdsort -o co1.tmd a.tmd
	cmplz co1.tmd co1.lz
	del a.tmd
	cd ..\..

$(COTOB_DIR)\cotobi1.lz:
	cd $(COTOB_DIR)
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
	timpos $(NAME)/name6.tim      896   0   0 487
	timpos $(NAMEVS)/namevs6.tim  896  16  16 487
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
	cmplz $(NAME)/name6.tim      name.lz
	cmplz $(NAMEVS)/namevs6.tim  namevs.lz
	hdlink /n /l ..\..\co1t.lis
	rsdlink cotobi.arg
	tmdsort -o cotobi1.tmd a.tmd
	cmplz cotobi1.tmd cotobi1.lz
	del a.tmd
	cd ..\..

co2.mod: $(CORCA_DIR)\co2.lz $(COTOB_DIR)\cotobi2.lz
	hdlink /n /l co2.lis

$(CORCA_DIR)\co2.lz:
	cd $(CORCA_DIR)
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
	tmdsort -o co2.tmd a.tmd
	cmplz co2.tmd co2.lz
	del a.tmd
	cd ..\..

$(COTOB_DIR)\cotobi2.lz:
	cd $(COTOB_DIR)
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
	timpos $(NAME)/name6.tim      926   0   0 495
	timpos $(NAMEVS)/namevs6.tim  896  56  16 495
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
	cmplz $(NAME)/name6.tim      name.lz
	cmplz $(NAMEVS)/namevs6.tim  namevs.lz
	hdlink /n /l ..\..\co2t.lis
	rsdlink cotobi.arg
	tmdsort -o cotobi2.tmd a.tmd
	cmplz cotobi2.tmd cotobi2.lz
	del a.tmd
	cd ..\..

co.mot: $(CORCA_DIR)\$(ANM_DIR)/coiki.lz \
		$(COTOB_DIR)\$(ANM_DIR)/cotob0.lz \
		$(COTOB_DIR)\$(ANM_DIR)/cotob1.lz
	hdlink /n /l co.lis

$(CORCA_DIR)\$(ANM_DIR)/coiki.lz:
	cd $(CORCA_DIR)\$(ANM_DIR)
	bin2mtn coiki
	cmplz coiki.mtn coiki.lz
	cd ..\..

$(COTOB_DIR)\$(ANM_DIR)/cotob0.lz:
	cd $(COTOB_DIR)\$(ANM_DIR)
	bin2mtn cotob0
	cmplz cotob0.mtn cotob0.lz
	cd ..\..

$(COTOB_DIR)\$(ANM_DIR)/cotob1.lz:
	cd $(COTOB_DIR)\$(ANM_DIR)
	bin2mtn cotob1
	cmplz cotob1.mtn cotob1.lz
	cd ..\..

