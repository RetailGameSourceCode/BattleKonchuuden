ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
BOLNEO_DIR=bliki\rsd
BLTOBI_DIR=bltobi\rsd

all : bl.mot bl1.mod bl2.mod
    psymake

bl1.mod: $(BOLNEO_DIR)\bl1.lz $(BLTOBI_DIR)\bltob1.lz
	hdlink /n /l bl1.lis

$(BOLNEO_DIR)\bl1.lz:
	cd $(BOLNEO_DIR)
	timpos $(TIM_DIR)/blhane.tim  320   0   0 480
	timpos $(TIM_DIR)/hane2.tim   424   0  64 482
	timpos $(TIM_DIR)/hara3.tim   424  56 128 482
	timpos $(TIM_DIR)/me.tim      440  56  96 482
	timpos $(TIM_DIR)/hara4.tim   448   0   0 481
	timpos $(TIM_DIR)/hara1.tim   448  80  32 482
	timpos $(TIM_DIR)/syokaku.tim 484 128 112 482
	timpos $(TIM_DIR)/hane1.tim   484 184  48 482
	timpos $(TIM_DIR)/hara2.tim   512   0  80 482
	timpos $(TIM_DIR)/at01.tim    512  72  16 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	rsdlink bliki.arg
	tmdsort -o bl1.tmd a.tmd
	cmplz bl1.tmd bl1.lz
	del a.tmd
	cd ..\..

$(BLTOBI_DIR)\bltob1.lz:
	cd $(BLTOBI_DIR)
	timpos $(TIM_DIR)/blhane.tim  320   0   0 480
	timpos $(TIM_DIR)/hane2.tim   424   0  64 482
	timpos $(TIM_DIR)/hara3.tim   424  56 128 482
	timpos $(TIM_DIR)/me.tim      440  56  96 482
	timpos $(TIM_DIR)/hara4.tim   448   0   0 481
	timpos $(TIM_DIR)/hara1.tim   448  80  32 482
	timpos $(TIM_DIR)/syokaku.tim 484 128 112 482
	timpos $(TIM_DIR)/hane1.tim   484 184  48 482
	timpos $(TIM_DIR)/hara2.tim   512   0  80 482
	timpos $(TIM_DIR)/at01.tim    512  72  16 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name7.tim      896   0   0 487
	timpos $(NAMEVS)/namevs7.tim  896  16  16 487
	cmplz $(TIM_DIR)/blhane.tim  blhane.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/at01.tim    at01.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name7.tim      name.lz
	cmplz $(NAMEVS)/namevs7.tim  namevs.lz
	hdlink /n /l ..\..\bl1t.lis
	rsdlink bltobi.arg
	tmdsort -o bltob1.tmd a.tmd
	cmplz bltob1.tmd bltob1.lz
	del a.tmd
	cd ..\..

bl2.mod: $(BOLNEO_DIR)\bl2.lz $(BLTOBI_DIR)\bltob2.lz
	hdlink /n /l bl2.lis

$(BOLNEO_DIR)\bl2.lz:
	cd $(BOLNEO_DIR)
	timpos $(TIM_DIR)/blhane.tim  576   0   0 488
	timpos $(TIM_DIR)/hane2.tim   680   0  64 490
	timpos $(TIM_DIR)/hara3.tim   680  56 128 490
	timpos $(TIM_DIR)/me.tim      696  56  96 490
	timpos $(TIM_DIR)/hara4.tim   704   0   0 489
	timpos $(TIM_DIR)/hara1.tim   704  80  32 490
	timpos $(TIM_DIR)/syokaku.tim 740 128 112 490
	timpos $(TIM_DIR)/hane1.tim   740 184  48 490
	timpos $(TIM_DIR)/hara2.tim   768   0  80 490
	timpos $(TIM_DIR)/at01.tim    768  72  16 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	rsdlink bliki.arg
	tmdsort -o bl2.tmd a.tmd
	cmplz bl2.tmd bl2.lz
	del a.tmd
	cd ..\..

$(BLTOBI_DIR)\bltob2.lz:
	cd $(BLTOBI_DIR)
	timpos $(TIM_DIR)/blhane.tim  576   0   0 488
	timpos $(TIM_DIR)/hane2.tim   680   0  64 490
	timpos $(TIM_DIR)/hara3.tim   680  56 128 490
	timpos $(TIM_DIR)/me.tim      696  56  96 490
	timpos $(TIM_DIR)/hara4.tim   704   0   0 489
	timpos $(TIM_DIR)/hara1.tim   704  80  32 490
	timpos $(TIM_DIR)/syokaku.tim 740 128 112 490
	timpos $(TIM_DIR)/hane1.tim   740 184  48 490
	timpos $(TIM_DIR)/hara2.tim   768   0  80 490
	timpos $(TIM_DIR)/at01.tim    768  72  16 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name7.tim      926   0   0 495
	timpos $(NAMEVS)/namevs7.tim  896  56  16 495
	cmplz $(TIM_DIR)/blhane.tim  blhane.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/at01.tim    at01.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name7.tim      name.lz
	cmplz $(NAMEVS)/namevs7.tim  namevs.lz
	hdlink /n /l ..\..\bl2t.lis
	rsdlink bltobi.arg
	tmdsort -o bltob2.tmd a.tmd
	cmplz bltob2.tmd bltob2.lz
	del a.tmd
	cd ..\..

bl.mot: $(BOLNEO_DIR)\$(ANM_DIR)/bliki.lz \
		$(BLTOBI_DIR)\$(ANM_DIR)/bltob0.lz \
		$(BLTOBI_DIR)\$(ANM_DIR)/bltob1.lz
	hdlink /n /l bl.lis

$(BOLNEO_DIR)\$(ANM_DIR)/bliki.lz:
	cd $(BOLNEO_DIR)\$(ANM_DIR)
	bin2mtn bliki
	cmplz bliki.mtn bliki.lz
	cd ..\..

$(BLTOBI_DIR)\$(ANM_DIR)/bltob0.lz:
	cd $(BLTOBI_DIR)\$(ANM_DIR)
	bin2mtn bltob0
	cmplz bltob0.mtn bltob0.lz
	cd ..\..

$(BLTOBI_DIR)\$(ANM_DIR)/bltob1.lz:
	cd $(BLTOBI_DIR)\$(ANM_DIR)
	bin2mtn bltob1
	cmplz bltob1.mtn bltob1.lz
	cd ..\..

