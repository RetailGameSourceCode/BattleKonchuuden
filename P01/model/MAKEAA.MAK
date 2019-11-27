ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
ATUSAM_DIR=35\rsd
ATUTOB_DIR=35tob\rsd

all : aa.mot aa1.mod aa2.mod
    psymake

aa1.mod: $(ATUSAM_DIR)\aa1.lz $(ATUTOB_DIR)\aatob1.lz
	hdlink /n /l aa1.lis

$(ATUSAM_DIR)\aa1.lz:
	cd $(ATUSAM_DIR)
	timpos $(TIM_DIR)/sese.tim    320   0   0 480
	timpos $(TIM_DIR)/hara2.tim   320 184  16 482
	timpos $(TIM_DIR)/hane2.tim   356   0  32 482
	timpos $(TIM_DIR)/ata2.tim    384   0   0 481
	timpos $(TIM_DIR)/headura.tim 384 144  48 482
	timpos $(TIM_DIR)/hara4.tim   416   0  64 482
	timpos $(TIM_DIR)/hane1.tim   416 192  80 482
	timpos $(TIM_DIR)/hara1.tim   448   0  96 482
	timpos $(TIM_DIR)/hara3.tim   448 160 112 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name35.tim     896   0   0 487
	timpos $(NAMEVS)/namevs35.tim 896  16  16 487
	cmplz $(TIM_DIR)/sese.tim    sese.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/ata2.tim    ata2.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name35.tim     name.lz
	cmplz $(NAMEVS)/namevs35.tim namevs.lz
	hdlink /n /l ..\..\aa1t.lis
	rsdlink 35.arg
	tmdsort -o aa1.tmd a.tmd
	cmplz aa1.tmd aa1.lz
	del a.tmd
	cd ..\..

$(ATUTOB_DIR)\aatob1.lz:
	cd $(ATUTOB_DIR)
	timpos $(TIM_DIR)/sese.tim    320   0   0 480
	timpos $(TIM_DIR)/hara2.tim   320 184  16 482
	timpos $(TIM_DIR)/hane2.tim   356   0  32 482
	timpos $(TIM_DIR)/ata2.tim    384   0   0 481
	timpos $(TIM_DIR)/headura.tim 384 144  48 482
	timpos $(TIM_DIR)/hara4.tim   416   0  64 482
	timpos $(TIM_DIR)/hane1.tim   416 192  80 482
	timpos $(TIM_DIR)/hara1.tim   448   0  96 482
	timpos $(TIM_DIR)/hara3.tim   448 160 112 482
	rsdlink 35tob.arg
	tmdsort -o aatob1.tmd a.tmd
	cmplz aatob1.tmd aatob1.lz
	del a.tmd
	cd ..\..

aa2.mod: $(ATUSAM_DIR)\aa2.lz $(ATUTOB_DIR)\aatob2.lz
	hdlink /n /l aa2.lis

$(ATUSAM_DIR)\aa2.lz:
	cd $(ATUSAM_DIR)
	timpos $(TIM_DIR)/sese.tim    576   0   0 488
	timpos $(TIM_DIR)/hara2.tim   576 184  16 490
	timpos $(TIM_DIR)/hane2.tim   612   0  32 490
	timpos $(TIM_DIR)/ata2.tim    640   0   0 489
	timpos $(TIM_DIR)/headura.tim 640 144  48 490
	timpos $(TIM_DIR)/hara4.tim   672   0  64 490
	timpos $(TIM_DIR)/hane1.tim   672 192  80 490
	timpos $(TIM_DIR)/hara1.tim   704   0  96 490
	timpos $(TIM_DIR)/hara3.tim   704 160 112 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name35.tim     926   0   0 495
	timpos $(NAMEVS)/namevs35.tim 896  56  16 495
	cmplz $(TIM_DIR)/sese.tim    sese.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/ata2.tim    ata2.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name35.tim     name.lz
	cmplz $(NAMEVS)/namevs35.tim namevs.lz
	hdlink /n /l ..\..\aa2t.lis
	rsdlink 35.arg
	tmdsort -o aa2.tmd a.tmd
	cmplz aa2.tmd aa2.lz
	del a.tmd
	cd ..\..

$(ATUTOB_DIR)\aatob2.lz:
	cd $(ATUTOB_DIR)
	timpos $(TIM_DIR)/sese.tim    576   0   0 488
	timpos $(TIM_DIR)/hara2.tim   576 184  16 490
	timpos $(TIM_DIR)/hane2.tim   612   0  32 490
	timpos $(TIM_DIR)/ata2.tim    640   0   0 489
	timpos $(TIM_DIR)/headura.tim 640 144  48 490
	timpos $(TIM_DIR)/hara4.tim   672   0  64 490
	timpos $(TIM_DIR)/hane1.tim   672 192  80 490
	timpos $(TIM_DIR)/hara1.tim   704   0  96 490
	timpos $(TIM_DIR)/hara3.tim   704 160 112 490
	rsdlink 35tob.arg
	tmdsort -o aatob2.tmd a.tmd
	cmplz aatob2.tmd aatob2.lz
	del a.tmd
	cd ..\..

aa.mot:
	hdlink /n /l aa.lis


