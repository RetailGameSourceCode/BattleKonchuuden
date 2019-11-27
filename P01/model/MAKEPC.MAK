ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
NOKO_DIR=46poke\rsd
NKTOB_DIR=nktob\rsd

all : pc1.mod pc2.mod
    psymake

pc1.mod: $(NOKO_DIR)\pc1.lz $(NKTOB_DIR)\pctob1.lz
	hdlink /n /l pc1.lis

$(NOKO_DIR)\pc1.lz:
	cd $(NOKO_DIR)
	timpos $(TIM_DIR)/skin.tim    448   0   0 480
	timpos $(TIM_DIR)/kuti.tim    448  64  16 482
	timpos $(TIM_DIR)/hana.tim    448 128  32 482
	timpos $(TIM_DIR)/ho.tim      448 192  48 482
	timpos $(TIM_DIR)/tuno.tim    464  64  64 482
	timpos $(TIM_DIR)/me.tim      464 128  80 482
	timpos $(TIM_DIR)/doutai.tim  512   0  96 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name57.tim     896   0   0 487
	timpos $(NAMEVS)/namevs57.tim 896  16  16 487
	cmplz $(TIM_DIR)/skin.tim    skin.lz
	cmplz $(TIM_DIR)/kuti.tim    kuti.lz
	cmplz $(TIM_DIR)/hana.tim    hana.lz
	cmplz $(TIM_DIR)/ho.tim      ho.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name57.tim     name.lz
	cmplz $(NAMEVS)/namevs57.tim namevs.lz
	hdlink /n /l ..\..\pc1t.lis
	rsdlink nk.arg
	tmdsort -o pc1.tmd a.tmd
	cmplz pc1.tmd pc1.lz
	cd ..\..

$(NKTOB_DIR)\pctob1.lz:
	cd $(NKTOB_DIR)
	timpos $(TIM_DIR)/body.tim    320   0   0 480
	timpos $(TIM_DIR)/mune.tim    384   0  16 480
	timpos $(TIM_DIR)/hara3.tim   384  96  32 480
	timpos $(TIM_DIR)/hara2.tim   384 176  48 480
	timpos $(TIM_DIR)/hara1.tim   448   0  64 480
	timpos $(TIM_DIR)/head.tim    512   0  80 480
	timpos $(TIM_DIR)/headura.tim 362   0  96 480
	timpos $(TIM_DIR)/me.tim      362  96 112 480
	timpos $(TIM_DIR)/hara4.tim   428   0 128 480
	timpos $(TIM_DIR)/hane1.tim   370  96 144 480
	timpos $(TIM_DIR)/hane2.tim   448 160 160 480
	rsdlink nktob1.arg
	tmdsort -o pctob1.tmd a.tmd
	cmplz pctob1.tmd pctob1.lz
	cd ..\..

pc2.mod: $(NOKO_DIR)\pc2.lz $(NKTOB_DIR)\pctob2.lz
	hdlink /n /l pc2.lis

$(NOKO_DIR)\pc2.lz:
	cd $(NOKO_DIR)
	timpos $(TIM_DIR)/skin.tim    704   0   0 488
	timpos $(TIM_DIR)/kuti.tim    704  64  16 490
	timpos $(TIM_DIR)/hana.tim    704 128  32 490
	timpos $(TIM_DIR)/ho.tim      704 192  48 490
	timpos $(TIM_DIR)/tuno.tim    720  64  64 490
	timpos $(TIM_DIR)/me.tim      720 128  80 490
	timpos $(TIM_DIR)/doutai.tim  768   0  96 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name57.tim     926   0   0 495
	timpos $(NAMEVS)/namevs57.tim 896  56  16 495
	cmplz $(TIM_DIR)/skin.tim    skin.lz
	cmplz $(TIM_DIR)/kuti.tim    kuti.lz
	cmplz $(TIM_DIR)/hana.tim    hana.lz
	cmplz $(TIM_DIR)/ho.tim      ho.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name57.tim     name.lz
	cmplz $(NAMEVS)/namevs57.tim namevs.lz
	hdlink /n /l ..\..\pc2t.lis
	rsdlink nk.arg
	tmdsort -o pc2.tmd a.tmd
	cmplz pc2.tmd pc2.lz
	cd ..\..

$(NKTOB_DIR)\pctob2.lz:
	cd $(NKTOB_DIR)
	timpos $(TIM_DIR)/body.tim    576   0   0 488
	timpos $(TIM_DIR)/mune.tim    640   0  16 488
	timpos $(TIM_DIR)/hara3.tim   640  96  32 488
	timpos $(TIM_DIR)/hara2.tim   640 176  48 488
	timpos $(TIM_DIR)/hara1.tim   704   0  64 488
	timpos $(TIM_DIR)/head.tim    768   0  80 488
	timpos $(TIM_DIR)/headura.tim 618   0  96 488
	timpos $(TIM_DIR)/me.tim      618  96 112 488
	timpos $(TIM_DIR)/hara4.tim   684   0 128 488
	timpos $(TIM_DIR)/hane1.tim   626  96 144 488
	timpos $(TIM_DIR)/hane2.tim   704 160 160 488
	rsdlink nktob1.arg
	tmdsort -o pctob2.tmd a.tmd
	cmplz pctob2.tmd pctob2.lz
	cd ..\..

