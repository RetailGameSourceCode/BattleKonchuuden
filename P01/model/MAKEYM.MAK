ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
RSD_DIR=22\rsd
TOB_DIR=22tob\rsd

all : ym.mot ym1.mod ym2.mod
    psymake

ym1.mod: $(RSD_DIR)\ym1.lz $(TOB_DIR)\ymtob1.lz
	hdlink /n /l ym1.lis

$(RSD_DIR)\ym1.lz:
	cd $(RSD_DIR)
	timpos $(TIM_DIR)/body.tim    320   0  16 482
	timpos $(TIM_DIR)/me.tim      376   0  32 482
	timpos $(TIM_DIR)/tuno.tim    376 112  48 482
	timpos $(TIM_DIR)/hara2.tim   384   0  64 482
	timpos $(TIM_DIR)/headura.tim 384  72  80 482
	timpos $(TIM_DIR)/syokaku.tim 384 168  96 482
	timpos $(TIM_DIR)/hige.tim    384 224 112 482
	timpos $(TIM_DIR)/kuti.tim    406  72 128 482
	timpos $(TIM_DIR)/head.tim    448   0 144 482
	timpos $(TIM_DIR)/hara3.tim   448 112 160 482
	rsdlink 22kbt.arg
	tmdsort -o ym1.tmd a.tmd
	cmplz ym1.tmd ym1.lz
	del a.tmd
	cd ..\..

$(TOB_DIR)\ymtob1.lz:
	cd $(TOB_DIR)
	timpos $(TIM_DIR)/body.tim    320   0  16 482
	timpos $(TIM_DIR)/me.tim      376   0  32 482
	timpos $(TIM_DIR)/tuno.tim    376 112  48 482
	timpos $(TIM_DIR)/hara2.tim   384   0  64 482
	timpos $(TIM_DIR)/headura.tim 384  72  80 482
	timpos $(TIM_DIR)/syokaku.tim 384 168  96 482
	timpos $(TIM_DIR)/hige.tim    384 224 112 482
	timpos $(TIM_DIR)/kuti.tim    406  72 128 482
	timpos $(TIM_DIR)/head.tim    448   0 144 482
	timpos $(TIM_DIR)/hara3.tim   448 112 160 482
	timpos $(TIM_DIR)/hara4.tim   428   0 176 482
	timpos $(TIM_DIR)/hane1.tim   428 192 192 482
	timpos $(TIM_DIR)/hane2.tim   448 192 208 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name22.tim     896   0   0 487
	timpos $(NAMEVS)/namevs22.tim 896  16  16 487
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/kuti.tim    kuti.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name22.tim     name.lz
	cmplz $(NAMEVS)/namevs22.tim namevs.lz
	hdlink /n /l ..\..\ym1t.lis
	rsdlink 22tob.arg
	tmdsort -o ymtob1.tmd a.tmd
	cmplz ymtob1.tmd ymtob1.lz
	del a.tmd
	cd ..\..

ym2.mod: $(RSD_DIR)\ym2.lz $(TOB_DIR)\ymtob2.lz
	hdlink /n /l ym2.lis

$(RSD_DIR)\ym2.lz:
	cd $(RSD_DIR)
	timpos $(TIM_DIR)/body.tim    576   0  16 490
	timpos $(TIM_DIR)/me.tim      632   0  32 490
	timpos $(TIM_DIR)/tuno.tim    632 112  48 490
	timpos $(TIM_DIR)/hara2.tim   640   0  64 490
	timpos $(TIM_DIR)/headura.tim 640  72  80 490
	timpos $(TIM_DIR)/syokaku.tim 640 168  96 490
	timpos $(TIM_DIR)/hige.tim    640 224 112 490
	timpos $(TIM_DIR)/kuti.tim    662  72 128 490
	timpos $(TIM_DIR)/head.tim    704   0 144 490
	timpos $(TIM_DIR)/hara3.tim   704 112 160 490
	rsdlink 22kbt.arg
	tmdsort -o ym2.tmd a.tmd
	cmplz ym2.tmd ym2.lz
	del a.tmd
	cd ..\..

$(TOB_DIR)\ymtob2.lz:
	cd $(TOB_DIR)
	timpos $(TIM_DIR)/body.tim    576   0  16 490
	timpos $(TIM_DIR)/me.tim      632   0  32 490
	timpos $(TIM_DIR)/tuno.tim    632 112  48 490
	timpos $(TIM_DIR)/hara2.tim   640   0  64 490
	timpos $(TIM_DIR)/headura.tim 640  72  80 490
	timpos $(TIM_DIR)/syokaku.tim 640 168  96 490
	timpos $(TIM_DIR)/hige.tim    640 224 112 490
	timpos $(TIM_DIR)/kuti.tim    662  72 128 490
	timpos $(TIM_DIR)/head.tim    704   0 144 490
	timpos $(TIM_DIR)/hara3.tim   704 112 160 490
	timpos $(TIM_DIR)/hara4.tim   684   0 176 490
	timpos $(TIM_DIR)/hane1.tim   684 192 192 490
	timpos $(TIM_DIR)/hane2.tim   704 192 208 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name22.tim     926   0   0 495
	timpos $(NAMEVS)/namevs22.tim 896  56  16 495
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/kuti.tim    kuti.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name22.tim     name.lz
	cmplz $(NAMEVS)/namevs22.tim namevs.lz
	hdlink /n /l ..\..\ym2t.lis
	rsdlink 22tob.arg
	tmdsort -o ymtob2.tmd a.tmd
	cmplz ymtob2.tmd ymtob2.lz
	del a.tmd
	cd ..\..

ym.mot:
	hdlink /n /l ym.lis



