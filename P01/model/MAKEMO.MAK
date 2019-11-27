ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
RSD_DIR=20\rsd
TOB_DIR=20tob\rsd

all : mo.mot mo1.mod mo2.mod
    psymake

mo1.mod: $(RSD_DIR)\mo1.lz $(TOB_DIR)\motob1.lz
	hdlink /n /l mo1.lis

$(RSD_DIR)\mo1.lz:
	cd $(RSD_DIR)
	timpos $(TIM_DIR)/body.tim    320   0  16 482
	timpos $(TIM_DIR)/me.tim      376   0  32 482
	timpos $(TIM_DIR)/tuno.tim    376 112  48 482
	timpos $(TIM_DIR)/hara2.tim   384   0  64 482
	timpos $(TIM_DIR)/headura.tim 384  72  80 482
	timpos $(TIM_DIR)/hige.tim    384 168  96 482
	timpos $(TIM_DIR)/kuti.tim    384 192 112 482
	timpos $(TIM_DIR)/head.tim    448   0 128 482
	timpos $(TIM_DIR)/hara3.tim   448 112 144 482
	timpos $(TIM_DIR)/syokaku.tim 492 128 160 482
	rsdlink 20kbt.arg
	tmdsort -o mo1.tmd a.tmd
	cmplz mo1.tmd mo1.lz
	del a.tmd
	cd ..\..

$(TOB_DIR)\motob1.lz:
	cd $(TOB_DIR)
	timpos $(TIM_DIR)/body.tim    320   0  16 482
	timpos $(TIM_DIR)/me.tim      376   0  32 482
	timpos $(TIM_DIR)/tuno.tim    376 112  48 482
	timpos $(TIM_DIR)/hara2.tim   384   0  64 482
	timpos $(TIM_DIR)/headura.tim 384  72  80 482
	timpos $(TIM_DIR)/hige.tim    384 168  96 482
	timpos $(TIM_DIR)/kuti.tim    384 192 112 482
	timpos $(TIM_DIR)/head.tim    448   0 128 482
	timpos $(TIM_DIR)/hara3.tim   448 112 144 482
	timpos $(TIM_DIR)/hane2.tim   448 192 176 482
	timpos $(TIM_DIR)/hane1.tim   472 192 192 482
	timpos $(TIM_DIR)/syokaku.tim 492 128 160 482
	timpos $(TIM_DIR)/hara4.tim   512   0   0 480
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name20.tim     896   0   0 487
	timpos $(NAMEVS)/namevs20.tim 896  16  16 487
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/kuti.tim    kuti.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name20.tim     name.lz
	cmplz $(NAMEVS)/namevs20.tim namevs.lz
	hdlink /n /l ..\..\mo1t.lis
	rsdlink 20tob.arg
	tmdsort -o motob1.tmd a.tmd
	cmplz motob1.tmd motob1.lz
	del a.tmd
	cd ..\..

mo2.mod: $(RSD_DIR)\mo2.lz $(TOB_DIR)\motob2.lz
	hdlink /n /l mo2.lis

$(RSD_DIR)\mo2.lz:
	cd $(RSD_DIR)
	timpos $(TIM_DIR)/body.tim    576   0  16 490
	timpos $(TIM_DIR)/me.tim      632   0  32 490
	timpos $(TIM_DIR)/tuno.tim    632 112  48 490
	timpos $(TIM_DIR)/hara2.tim   640   0  64 490
	timpos $(TIM_DIR)/headura.tim 640  72  80 490
	timpos $(TIM_DIR)/hige.tim    640 168  96 490
	timpos $(TIM_DIR)/kuti.tim    640 192 112 490
	timpos $(TIM_DIR)/head.tim    704   0 128 490
	timpos $(TIM_DIR)/hara3.tim   704 112 144 490
	timpos $(TIM_DIR)/syokaku.tim 748 128 160 490
	rsdlink 20kbt.arg
	tmdsort -o mo2.tmd a.tmd
	cmplz mo2.tmd mo2.lz
	del a.tmd
	cd ..\..

$(TOB_DIR)\motob2.lz:
	cd $(TOB_DIR)
	timpos $(TIM_DIR)/body.tim    576   0  16 490
	timpos $(TIM_DIR)/me.tim      632   0  32 490
	timpos $(TIM_DIR)/tuno.tim    632 112  48 490
	timpos $(TIM_DIR)/hara2.tim   640   0  64 490
	timpos $(TIM_DIR)/headura.tim 640  72  80 490
	timpos $(TIM_DIR)/hige.tim    640 168  96 490
	timpos $(TIM_DIR)/kuti.tim    640 192 112 490
	timpos $(TIM_DIR)/head.tim    704   0 128 490
	timpos $(TIM_DIR)/hara3.tim   704 112 144 490
	timpos $(TIM_DIR)/hane2.tim   704 192 176 490
	timpos $(TIM_DIR)/hane1.tim   728 192 192 490
	timpos $(TIM_DIR)/syokaku.tim 748 128 160 490
	timpos $(TIM_DIR)/hara4.tim   768   0   0 488
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name20.tim     926   0   0 495
	timpos $(NAMEVS)/namevs20.tim 896  56  16 495
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/kuti.tim    kuti.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name20.tim     name.lz
	cmplz $(NAMEVS)/namevs20.tim namevs.lz
	hdlink /n /l ..\..\mo2t.lis
	rsdlink 20tob.arg
	tmdsort -o motob2.tmd a.tmd
	cmplz motob2.tmd motob2.lz
	del a.tmd
	cd ..\..

mo.mot:
	hdlink /n /l mo.lis

