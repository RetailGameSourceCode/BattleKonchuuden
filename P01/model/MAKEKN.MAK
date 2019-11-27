ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
KIBANA_DIR=36\rsd
KIBATOB_DIR=36tob\rsd

all : kn.mot kn1.mod kn2.mod
    psymake

kn1.mod: $(KIBANA_DIR)\kn1.lz $(KIBATOB_DIR)\kntob1.lz
	hdlink /n /l kn1.lis

$(KIBANA_DIR)\kn1.lz:
	cd $(KIBANA_DIR)
	timpos $(TIM_DIR)/body.tim    320   0  16 482
	timpos $(TIM_DIR)/headura.tim 362   0  32 482
	timpos $(TIM_DIR)/me.tim      362  96  48 482
	timpos $(TIM_DIR)/hara1.tim   384   0  64 482
	timpos $(TIM_DIR)/mune.tim    384 160  80 482
	timpos $(TIM_DIR)/head.tim    448   0  96 482
	timpos $(TIM_DIR)/hara3.tim   448 112 112 482
	timpos $(TIM_DIR)/hara2.tim   512   0 128 482
	rsdlink 36.arg
	tmdsort -o kn1.tmd a.tmd
	cmplz kn1.tmd kn1.lz
	del a.tmd
	cd ..\..

$(KIBATOB_DIR)\kntob1.lz:
	cd $(KIBATOB_DIR)
	timpos $(TIM_DIR)/body.tim    320   0  16 482
	timpos $(TIM_DIR)/headura.tim 362   0  32 482
	timpos $(TIM_DIR)/me.tim      362  96  48 482
	timpos $(TIM_DIR)/hara1.tim   384   0  64 482
	timpos $(TIM_DIR)/mune.tim    384 160  80 482
	timpos $(TIM_DIR)/head.tim    448   0  96 482
	timpos $(TIM_DIR)/hara3.tim   448 112 112 482
	timpos $(TIM_DIR)/hara2.tim   512   0 128 482
	timpos $(TIM_DIR)/hara4.tim   428   0 144 482
	timpos $(TIM_DIR)/hane1.tim   428 192 160 482
	timpos $(TIM_DIR)/hane2.tim   448 192 176 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name36.tim     896   0   0 487
	timpos $(NAMEVS)/namevs36.tim 896  16  16 487
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name36.tim     name.lz
	cmplz $(NAMEVS)/namevs36.tim namevs.lz
	hdlink /n /l ..\..\kn1t.lis
	rsdlink 36tob.arg
	tmdsort -o kntob1.tmd a.tmd
	cmplz kntob1.tmd kntob1.lz
	del a.tmd
	cd ..\..

kn2.mod: $(KIBANA_DIR)\kn2.lz $(KIBATOB_DIR)\kntob2.lz
	hdlink /n /l kn2.lis

$(KIBANA_DIR)\kn2.lz:
	cd $(KIBANA_DIR)
	timpos $(TIM_DIR)/body.tim    576   0  16 490
	timpos $(TIM_DIR)/headura.tim 618   0  32 490
	timpos $(TIM_DIR)/me.tim      618  96  48 490
	timpos $(TIM_DIR)/hara1.tim   640   0  64 490
	timpos $(TIM_DIR)/mune.tim    640 160  80 490
	timpos $(TIM_DIR)/head.tim    704   0  96 490
	timpos $(TIM_DIR)/hara3.tim   704 112 112 490
	timpos $(TIM_DIR)/hara2.tim   768   0 128 490
	rsdlink 36.arg
	tmdsort -o kn2.tmd a.tmd
	cmplz kn2.tmd kn2.lz
	del a.tmd
	cd ..\..

$(KIBATOB_DIR)\kntob2.lz:
	cd $(KIBATOB_DIR)
	timpos $(TIM_DIR)/body.tim    576   0  16 490
	timpos $(TIM_DIR)/headura.tim 618   0  32 490
	timpos $(TIM_DIR)/me.tim      618  96  48 490
	timpos $(TIM_DIR)/hara1.tim   640   0  64 490
	timpos $(TIM_DIR)/mune.tim    640 160  80 490
	timpos $(TIM_DIR)/head.tim    704   0  96 490
	timpos $(TIM_DIR)/hara3.tim   704 112 112 490
	timpos $(TIM_DIR)/hara2.tim   768   0 128 490
	timpos $(TIM_DIR)/hara4.tim   684   0 144 490
	timpos $(TIM_DIR)/hane1.tim   684 192 160 490
	timpos $(TIM_DIR)/hane2.tim   704 192 176 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name36.tim     926   0   0 495
	timpos $(NAMEVS)/namevs36.tim 896  56  16 495
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name36.tim     name.lz
	cmplz $(NAMEVS)/namevs36.tim namevs.lz
	hdlink /n /l ..\..\kn2t.lis
	rsdlink 36tob.arg
	tmdsort -o kntob2.tmd a.tmd
	cmplz kntob2.tmd kntob2.lz
	del a.tmd
	cd ..\..

kn.mot:
	hdlink /n /l kn.lis


