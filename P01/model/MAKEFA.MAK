ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
FUCHI_DIR=34\rsd
FUCHITOB_DIR=34tob\rsd

all : fa.mot fa1.mod fa2.mod
    psymake

fa1.mod: $(FUCHI_DIR)\fa1.lz $(FUCHITOB_DIR)\fatob1.lz
	hdlink /n /l fa1.lis

$(FUCHI_DIR)\fa1.lz:
	cd $(FUCHI_DIR)
	timpos $(TIM_DIR)/senaka.tim  320   0   0 480
	timpos $(TIM_DIR)/atama.tim   384   0   0 481
	timpos $(TIM_DIR)/hara2.tim   384 184  16 482
	timpos $(TIM_DIR)/hane2.tim   404 184  32 482
	timpos $(TIM_DIR)/hara4.tim   448   0  48 482
	timpos $(TIM_DIR)/hane1.tim   448 192  64 482
	timpos $(TIM_DIR)/hara1.tim   464   0  80 482
	rsdlink 34iki.arg
	tmdsort -o fa1.tmd a.tmd
	cmplz fa1.tmd fa1.lz
	del a.tmd
	cd ..\..

$(FUCHITOB_DIR)\fatob1.lz:
	cd $(FUCHITOB_DIR)
	timpos $(TIM_DIR)/senaka.tim  320   0   0 480
	timpos $(TIM_DIR)/atama.tim   384   0   0 481
	timpos $(TIM_DIR)/hara2.tim   384 184  16 482
	timpos $(TIM_DIR)/hane2.tim   404 184  32 482
	timpos $(TIM_DIR)/hara4.tim   448   0  48 482
	timpos $(TIM_DIR)/hane1.tim   448 192  64 482
	timpos $(TIM_DIR)/hara1.tim   464   0  80 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name34.tim     896   0   0 487
	timpos $(NAMEVS)/namevs34.tim 896  16  16 487
	cmplz $(TIM_DIR)/senaka.tim  senaka.lz
	cmplz $(TIM_DIR)/atama.tim   atama.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name34.tim     name.lz
	cmplz $(NAMEVS)/namevs34.tim namevs.lz
	hdlink /n /l ..\..\fa1t.lis
	rsdlink 34tob.arg
	tmdsort -o fatob1.tmd a.tmd
	cmplz fatob1.tmd fatob1.lz
	del a.tmd
	cd ..\..

fa2.mod: $(FUCHI_DIR)\fa2.lz $(FUCHITOB_DIR)\fatob2.lz
	hdlink /n /l fa2.lis

$(FUCHI_DIR)\fa2.lz:
	cd $(FUCHI_DIR)
	timpos $(TIM_DIR)/senaka.tim  576   0   0 488
	timpos $(TIM_DIR)/atama.tim   640   0   0 489
	timpos $(TIM_DIR)/hara2.tim   640 184  16 490
	timpos $(TIM_DIR)/hane2.tim   660 184  32 490
	timpos $(TIM_DIR)/hara4.tim   704   0  48 490
	timpos $(TIM_DIR)/hane1.tim   704 192  64 490
	timpos $(TIM_DIR)/hara1.tim   720   0  80 490
	rsdlink 34iki.arg
	tmdsort -o fa2.tmd a.tmd
	cmplz fa2.tmd fa2.lz
	del a.tmd
	cd ..\..

$(FUCHITOB_DIR)\fatob2.lz:
	cd $(FUCHITOB_DIR)
	timpos $(TIM_DIR)/senaka.tim  576   0   0 488
	timpos $(TIM_DIR)/atama.tim   640   0   0 489
	timpos $(TIM_DIR)/hara2.tim   640 184  16 490
	timpos $(TIM_DIR)/hane2.tim   660 184  32 490
	timpos $(TIM_DIR)/hara4.tim   704   0  48 490
	timpos $(TIM_DIR)/hane1.tim   704 192  64 490
	timpos $(TIM_DIR)/hara1.tim   720   0  80 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name34.tim     926   0   0 495
	timpos $(NAMEVS)/namevs34.tim 896  56  16 495
	cmplz $(TIM_DIR)/senaka.tim  senaka.lz
	cmplz $(TIM_DIR)/atama.tim   atama.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name34.tim     name.lz
	cmplz $(NAMEVS)/namevs34.tim namevs.lz
	hdlink /n /l ..\..\fa2t.lis
	rsdlink 34tob.arg
	tmdsort -o fatob2.tmd a.tmd
	cmplz fatob2.tmd fatob2.lz
	del a.tmd
	cd ..\..

fa.mot:
	hdlink /n /l fa.lis

