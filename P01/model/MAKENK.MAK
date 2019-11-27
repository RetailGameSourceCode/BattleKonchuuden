ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
NOKO_DIR=nokogiri\rsd
NKTOB_DIR=nktob\rsd

all : nk.mot nk1.mod nk2.mod
    psymake

nk1.mod: $(NOKO_DIR)\nk1.lz $(NKTOB_DIR)\nktob1.lz
	hdlink /n /l nk1.lis

$(NOKO_DIR)\nk1.lz:
	cd $(NOKO_DIR)
	timpos $(TIM_DIR)/body.tim    320   0   0 480
	timpos $(TIM_DIR)/mune.tim    384   0  16 480
	timpos $(TIM_DIR)/hara3.tim   384  96  32 480
	timpos $(TIM_DIR)/hara2.tim   384 176  48 480
	timpos $(TIM_DIR)/hara1.tim   448   0  64 480
	timpos $(TIM_DIR)/head.tim    512   0  80 480
	timpos $(TIM_DIR)/headura.tim 362   0  96 480
	timpos $(TIM_DIR)/me.tim      362  96 112 480
	timpos $(TIM_DIR)/hara4.tim   428   0 128 480
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	rsdlink nk.arg
	tmdsort -o nk1.tmd a.tmd
	cmplz nk1.tmd nk1.lz
	cd ..\..

$(NKTOB_DIR)\nktob1.lz:
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
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name46.tim     896   0   0 487
	timpos $(NAMEVS)/namevs46.tim 896  16  16 487
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name46.tim     name.lz
	cmplz $(NAMEVS)/namevs46.tim namevs.lz
	hdlink /n /l ..\..\nk1t.lis
	rsdlink nktob1.arg
	tmdsort -o nktob1.tmd a.tmd
	cmplz nktob1.tmd nktob1.lz
	cd ..\..

nk2.mod: $(NOKO_DIR)\nk2.lz $(NKTOB_DIR)\nktob2.lz
	hdlink /n /l nk2.lis

$(NOKO_DIR)\nk2.lz:
	cd $(NOKO_DIR)
	timpos $(TIM_DIR)/body.tim    576   0   0 488
	timpos $(TIM_DIR)/mune.tim    640   0  16 488
	timpos $(TIM_DIR)/hara3.tim   640  96  32 488
	timpos $(TIM_DIR)/hara2.tim   640 176  48 488
	timpos $(TIM_DIR)/hara1.tim   704   0  64 488
	timpos $(TIM_DIR)/head.tim    768   0  80 488
	timpos $(TIM_DIR)/headura.tim 618   0  96 488
	timpos $(TIM_DIR)/me.tim      618  96 112 488
	timpos $(TIM_DIR)/hara4.tim   684   0 128 488
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	rsdlink nk.arg
	tmdsort -o nk2.tmd a.tmd
	cmplz nk2.tmd nk2.lz
	cd ..\..

$(NKTOB_DIR)\nktob2.lz:
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
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name46.tim     926   0   0 495
	timpos $(NAMEVS)/namevs46.tim 896  56  16 495
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name46.tim     name.lz
	cmplz $(NAMEVS)/namevs46.tim namevs.lz
	hdlink /n /l ..\..\nk2t.lis
	rsdlink nktob1.arg
	tmdsort -o nktob2.tmd a.tmd
	cmplz nktob2.tmd nktob2.lz
	cd ..\..

nk.mot: $(NOKO_DIR)\$(ANM_DIR)/nkiki.lz \
		$(NKTOB_DIR)\$(ANM_DIR)/nktob0.lz \
		$(NKTOB_DIR)\$(ANM_DIR)/nktob1.lz
	hdlink /n /l nk.lis

$(NOKO_DIR)\$(ANM_DIR)/nkiki.lz:
	cd $(NOKO_DIR)\$(ANM_DIR)
	bin2mtn nkiki
	cmplz nkiki.mtn nkiki.lz
	cd ..\..

$(NKTOB_DIR)\$(ANM_DIR)/nktob0.lz:
	cd $(NKTOB_DIR)\$(ANM_DIR)
	bin2mtn nktob0
	cmplz nktob0.mtn nktob0.lz
	cd ..\..

$(NKTOB_DIR)\$(ANM_DIR)/nktob1.lz:
	cd $(NKTOB_DIR)\$(ANM_DIR)
	bin2mtn nktob1
	cmplz nktob1.mtn nktob1.lz
	cd ..\..


