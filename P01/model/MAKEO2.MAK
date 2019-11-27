ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
ATUSAM_DIR=33\rsd
ATUTOB_DIR=33tob\rsd

all : o2.mot o21.mod o22.mod
    psymake

o21.mod: $(ATUSAM_DIR)\o21.lz $(ATUTOB_DIR)\o2tob1.lz
	hdlink /n /l o21.lis

$(ATUSAM_DIR)\o21.lz:
	cd $(ATUSAM_DIR)
	timpos $(TIM_DIR)/hara2.tim   448   0  32 482
	timpos $(TIM_DIR)/hara1.tim   448  72  48 482
	timpos $(TIM_DIR)/head.tim    484 128  64 482
	timpos $(TIM_DIR)/tuno.tim    484 192  80 482
	timpos $(TIM_DIR)/headura.tim 500 128  96 482
	timpos $(TIM_DIR)/head2.tim   512 192 128 482
	timpos $(TIM_DIR)/doutai.tim  544   0 160 482
	timpos $(TIM_DIR)/skin.tim    544 160 176 482
	timpos $(TIM_DIR)/me.tim      544 208 192 482
	rsdlink 33iki.arg
	tmdsort -o o21.tmd a.tmd
	cmplz o21.tmd o21.lz
	del a.tmd
	cd ..\..

$(ATUTOB_DIR)\o2tob1.lz:
	cd $(ATUTOB_DIR)
	timpos $(TIM_DIR)/hane2.tim   384   0  16 482
	timpos $(TIM_DIR)/hara2.tim   448   0  32 482
	timpos $(TIM_DIR)/hara1.tim   448  72  48 482
	timpos $(TIM_DIR)/head.tim    484 128  64 482
	timpos $(TIM_DIR)/tuno.tim    484 192  80 482
	timpos $(TIM_DIR)/headura.tim 500 128  96 482
	timpos $(TIM_DIR)/hara4.tim   512   0   0 480
	timpos $(TIM_DIR)/head2.tim   512 192 128 482
	timpos $(TIM_DIR)/hane1.tim   528 192 144 482
	timpos $(TIM_DIR)/doutai.tim  544   0 160 482
	timpos $(TIM_DIR)/skin.tim    544 160 176 482
	timpos $(TIM_DIR)/me.tim      544 208 192 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name33.tim     896   0   0 487
	timpos $(NAMEVS)/namevs33.tim 896  16  16 487
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/head2.tim   head2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/skin.tim    skin.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name33.tim     name.lz
	cmplz $(NAMEVS)/namevs33.tim namevs.lz
	hdlink /n /l ..\..\o21t.lis
	rsdlink 33tob.arg
	tmdsort -o o2tob1.tmd a.tmd
	cmplz o2tob1.tmd o2tob1.lz
	del a.tmd
	cd ..\..

o22.mod: $(ATUSAM_DIR)\o22.lz $(ATUTOB_DIR)\o2tob2.lz
	hdlink /n /l o22.lis

$(ATUSAM_DIR)\o22.lz:
	cd $(ATUSAM_DIR)
	timpos $(TIM_DIR)/hara2.tim   704   0  32 490
	timpos $(TIM_DIR)/hara1.tim   704  72  48 490
	timpos $(TIM_DIR)/head.tim    740 128  64 490
	timpos $(TIM_DIR)/tuno.tim    740 192  80 490
	timpos $(TIM_DIR)/headura.tim 756 128  96 490
	timpos $(TIM_DIR)/head2.tim   768 192 128 490
	timpos $(TIM_DIR)/doutai.tim  800   0 160 490
	timpos $(TIM_DIR)/skin.tim    800 160 176 490
	timpos $(TIM_DIR)/me.tim      800 208 192 490
	rsdlink 33iki.arg
	tmdsort -o o22.tmd a.tmd
	cmplz o22.tmd o22.lz
	del a.tmd
	cd ..\..

$(ATUTOB_DIR)\o2tob2.lz:
	cd $(ATUTOB_DIR)
	timpos $(TIM_DIR)/hane2.tim   640   0  16 490
	timpos $(TIM_DIR)/hara2.tim   704   0  32 490
	timpos $(TIM_DIR)/hara1.tim   704  72  48 490
	timpos $(TIM_DIR)/head.tim    740 128  64 490
	timpos $(TIM_DIR)/tuno.tim    740 192  80 490
	timpos $(TIM_DIR)/headura.tim 756 128  96 490
	timpos $(TIM_DIR)/hara4.tim   768   0   0 488
	timpos $(TIM_DIR)/head2.tim   768 192 128 490
	timpos $(TIM_DIR)/hane1.tim   784 192 144 490
	timpos $(TIM_DIR)/doutai.tim  800   0 160 490
	timpos $(TIM_DIR)/skin.tim    800 160 176 490
	timpos $(TIM_DIR)/me.tim      800 208 192 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name33.tim     926   0   0 495
	timpos $(NAMEVS)/namevs33.tim 896  56  16 495
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/head2.tim   head2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/skin.tim    skin.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name33.tim     name.lz
	cmplz $(NAMEVS)/namevs33.tim namevs.lz
	hdlink /n /l ..\..\o22t.lis
	rsdlink 33tob.arg
	tmdsort -o o2tob2.tmd a.tmd
	cmplz o2tob2.tmd o2tob2.lz
	del a.tmd
	cd ..\..

o2.mot:
	hdlink /n /l o2.lis


