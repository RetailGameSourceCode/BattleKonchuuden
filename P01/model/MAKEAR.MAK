ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
ARAME_DIR=arkbt\rsd
ARTOB=artob\rsd

all : ar.mot ar1.mod ar2.mod
    psymake

ar1.mod: $(ARAME_DIR)\ar1.lz $(ARTOB)\artob1.lz
	hdlink /n /l ar1.lis

$(ARAME_DIR)\ar1.lz:
	cd $(ARAME_DIR)
	timpos $(TIM_DIR)/body.tim    320   0  16 482
	timpos $(TIM_DIR)/me.tim      376   0  32 482
	timpos $(TIM_DIR)/tuno.tim    376 112  48 482
	timpos $(TIM_DIR)/head.tim    384   0  64 482
	timpos $(TIM_DIR)/ohige.tim   384 112  80 482
	timpos $(TIM_DIR)/syokaku.tim 428   0  96 482
	timpos $(TIM_DIR)/headura.tim 420 112 112 482
	timpos $(TIM_DIR)/kuti.tim    420 208 128 482
	timpos $(TIM_DIR)/hige.tim    432 208 144 482
	timpos $(TIM_DIR)/hara2.tim   448   0 160 482
	timpos $(TIM_DIR)/hara3.tim   448  72 176 482
	rsdlink arkbt.arg
	tmdsort -o ar1.tmd a.tmd
	cmplz ar1.tmd ar1.lz
	del a.tmd
	cd ..\..

$(ARTOB)\artob1.lz:
	cd $(ARTOB)
	timpos $(TIM_DIR)/body.tim    320   0  16 482
	timpos $(TIM_DIR)/me.tim      376   0  32 482
	timpos $(TIM_DIR)/tuno.tim    376 112  48 482
	timpos $(TIM_DIR)/head.tim    384   0  64 482
	timpos $(TIM_DIR)/ohige.tim   384 112  80 482
	timpos $(TIM_DIR)/syokaku.tim 428   0  96 482
	timpos $(TIM_DIR)/headura.tim 420 112 112 482
	timpos $(TIM_DIR)/kuti.tim    420 208 128 482
	timpos $(TIM_DIR)/hige.tim    432 208 144 482
	timpos $(TIM_DIR)/hara2.tim   448   0 160 482
	timpos $(TIM_DIR)/hara3.tim   448  72 176 482
	timpos $(TIM_DIR)/hane2.tim   448 152 192 482
	timpos $(TIM_DIR)/hane1.tim   472 152 208 482
	timpos $(TIM_DIR)/hara4.tim   512   0 224 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name23.tim     896   0   0 487
	timpos $(NAMEVS)/namevs23.tim 896  16  16 487
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/ohige.tim   ohige.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/kuti.tim    kuti.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name23.tim     name.lz
	cmplz $(NAMEVS)/namevs23.tim namevs.lz
	hdlink /n /l ..\..\ar1t.lis
	rsdlink artob.arg
	tmdsort -o artob1.tmd a.tmd
	cmplz artob1.tmd artob1.lz
	del a.tmd
	cd ..\..

ar2.mod: $(ARAME_DIR)\ar2.lz $(ARTOB)\artob2.lz
	hdlink /n /l ar2.lis

$(ARAME_DIR)\ar2.lz:
	cd $(ARAME_DIR)
	timpos $(TIM_DIR)/body.tim    576   0  16 490
	timpos $(TIM_DIR)/me.tim      632   0  32 490
	timpos $(TIM_DIR)/tuno.tim    632 112  48 490
	timpos $(TIM_DIR)/head.tim    640   0  64 490
	timpos $(TIM_DIR)/ohige.tim   640 112  80 490
	timpos $(TIM_DIR)/syokaku.tim 684   0  96 490
	timpos $(TIM_DIR)/headura.tim 676 112 112 490
	timpos $(TIM_DIR)/kuti.tim    676 208 128 490
	timpos $(TIM_DIR)/hige.tim    688 208 144 490
	timpos $(TIM_DIR)/hara2.tim   704   0 160 490
	timpos $(TIM_DIR)/hara3.tim   704  72 176 490
	rsdlink arkbt.arg
	tmdsort -o ar2.tmd a.tmd
	cmplz ar2.tmd ar2.lz
	del a.tmd
	cd ..\..

$(ARTOB)\artob2.lz:
	cd $(ARTOB)
	timpos $(TIM_DIR)/body.tim    576   0  16 490
	timpos $(TIM_DIR)/me.tim      632   0  32 490
	timpos $(TIM_DIR)/tuno.tim    632 112  48 490
	timpos $(TIM_DIR)/head.tim    640   0  64 490
	timpos $(TIM_DIR)/ohige.tim   640 112  80 490
	timpos $(TIM_DIR)/syokaku.tim 684   0  96 490
	timpos $(TIM_DIR)/headura.tim 676 112 112 490
	timpos $(TIM_DIR)/kuti.tim    676 208 128 490
	timpos $(TIM_DIR)/hige.tim    688 208 144 490
	timpos $(TIM_DIR)/hara2.tim   704   0 160 490
	timpos $(TIM_DIR)/hara3.tim   704  72 176 490
	timpos $(TIM_DIR)/hane2.tim   704 152 192 490
	timpos $(TIM_DIR)/hane1.tim   728 152 208 490
	timpos $(TIM_DIR)/hara4.tim   768   0 224 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name23.tim     926   0   0 495
	timpos $(NAMEVS)/namevs23.tim 896  56  16 495
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/ohige.tim   ohige.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/kuti.tim    kuti.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name23.tim     name.lz
	cmplz $(NAMEVS)/namevs23.tim namevs.lz
	hdlink /n /l ..\..\ar2t.lis
	rsdlink artob.arg
	tmdsort -o artob2.tmd a.tmd
	cmplz artob2.tmd artob2.lz
	del a.tmd
	cd ..\..

ar.mot:
	hdlink /n /l ar.lis

