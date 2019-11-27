ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
MIYAMA_DIR=miyama\rsd
MYTOB_DIR=mymtb\rsd

all : my.mot my1.mod my2.mod
    psymake

my1.mod: $(MIYAMA_DIR)\my1.lz $(MYTOB_DIR)\mytob1.lz
	hdlink /n /l my1.lis

$(MIYAMA_DIR)\my1.lz:
	cd $(MIYAMA_DIR)
	timpos $(TIM_DIR)/body256.tim 320   0   0 484
	timpos $(TIM_DIR)/hasami.tim  364   0  16 482
	timpos $(TIM_DIR)/me.tim      376   0  48 482
	timpos $(TIM_DIR)/hara1256.tim 384  0   0 485
	timpos $(TIM_DIR)/mune.tim    384 160   0 481
	timpos $(TIM_DIR)/hara2.tim   448   0  32 482
	timpos $(TIM_DIR)/headura.tim 448  72  64 482
	timpos $(TIM_DIR)/hara3.tim   448 168  80 482
	timpos $(TIM_DIR)/head.tim    512   0   0 480
	timpos $(TIM_DIR)/hara3256.tim 512 112  0 483
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	rsdlink my00.arg
	tmdsort -o my1.tmd a.tmd
	cmplz my1.tmd my1.lz
	del a.tmd
	cd ..\..

$(MYTOB_DIR)\mytob1.lz:
	cd $(MYTOB_DIR)
	timpos $(TIM_DIR)/body256.tim 320   0   0 484
	timpos $(TIM_DIR)/hasami.tim  364   0  16 482
	timpos $(TIM_DIR)/me.tim      376   0  48 482
	timpos $(TIM_DIR)/hara1256.tim 384  0   0 485
	timpos $(TIM_DIR)/mune.tim    384 160   0 481
	timpos $(TIM_DIR)/hara2.tim   448   0  32 482
	timpos $(TIM_DIR)/headura.tim 448  72  64 482
	timpos $(TIM_DIR)/hara3.tim   448 168  80 482
	timpos $(TIM_DIR)/head.tim    512   0   0 480
	timpos $(TIM_DIR)/hara3256.tim 512 112  0 483
	timpos $(TIM_DIR)/hara4.tim   428   0 128 482
	timpos $(TIM_DIR)/hane1.tim   428 192 112 482
	timpos $(TIM_DIR)/hane2.tim   512 192  96 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name29.tim     896   0   0 487
	timpos $(NAMEVS)/namevs29.tim 896  16  16 487
	cmplz $(TIM_DIR)/body256.tim body256.lz
	cmplz $(TIM_DIR)/hasami.tim  hasami.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara1256.tim hara1256.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara3256.tim hara3256.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name29.tim     name.lz
	cmplz $(NAMEVS)/namevs29.tim namevs.lz
	hdlink /n /l ..\..\my1t.lis
	rsdlink mytb.arg
	tmdsort -o mytob1.tmd a.tmd
	cmplz mytob1.tmd mytob1.lz
	del a.tmd
	cd ..\..

my2.mod: $(MIYAMA_DIR)\my2.lz $(MYTOB_DIR)\mytob2.lz
	hdlink /n /l my2.lis

$(MIYAMA_DIR)\my2.lz:
	cd $(MIYAMA_DIR)
	timpos $(TIM_DIR)/body256.tim 576   0   0 492
	timpos $(TIM_DIR)/hasami.tim  620   0  16 490
	timpos $(TIM_DIR)/me.tim      632   0  48 490
	timpos $(TIM_DIR)/hara1256.tim 640  0   0 493
	timpos $(TIM_DIR)/mune.tim    640 160   0 489
	timpos $(TIM_DIR)/hara2.tim   704   0  32 490
	timpos $(TIM_DIR)/headura.tim 704  72  64 490
	timpos $(TIM_DIR)/hara3.tim   704 168  80 490
	timpos $(TIM_DIR)/head.tim    768   0   0 488
	timpos $(TIM_DIR)/hara3256.tim 768 112  0 491
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	rsdlink my00.arg
	tmdsort -o my2.tmd a.tmd
	cmplz my2.tmd my2.lz
	del a.tmd
	cd ..\..

$(MYTOB_DIR)\mytob2.lz:
	cd $(MYTOB_DIR)
	timpos $(TIM_DIR)/body256.tim 576   0   0 492
	timpos $(TIM_DIR)/hasami.tim  620   0  16 490
	timpos $(TIM_DIR)/me.tim      632   0  48 490
	timpos $(TIM_DIR)/hara1256.tim 640  0   0 493
	timpos $(TIM_DIR)/mune.tim    640 160   0 489
	timpos $(TIM_DIR)/hara2.tim   704   0  32 490
	timpos $(TIM_DIR)/headura.tim 704  72  64 490
	timpos $(TIM_DIR)/hara3.tim   704 168  80 490
	timpos $(TIM_DIR)/head.tim    768   0   0 488
	timpos $(TIM_DIR)/hara3256.tim 768 112  0 491
	timpos $(TIM_DIR)/hara4.tim   684   0 128 490
	timpos $(TIM_DIR)/hane1.tim   684 192 112 490
	timpos $(TIM_DIR)/hane2.tim   768 192  96 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name29.tim     926   0   0 495
	timpos $(NAMEVS)/namevs29.tim 896  56  16 495
	cmplz $(TIM_DIR)/body256.tim body256.lz
	cmplz $(TIM_DIR)/hasami.tim  hasami.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara1256.tim hara1256.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara3256.tim hara3256.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name29.tim     name.lz
	cmplz $(NAMEVS)/namevs29.tim namevs.lz
	hdlink /n /l ..\..\my2t.lis
	rsdlink mytb.arg
	tmdsort -o mytob2.tmd a.tmd
	cmplz mytob2.tmd mytob2.lz
	del a.tmd
	cd ..\..

my.mot: $(MIYAMA_DIR)\$(ANM_DIR)/myiki.lz \
		$(MYTOB_DIR)\$(ANM_DIR)/mytb0.lz \
		$(MYTOB_DIR)\$(ANM_DIR)/mytb1.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/myatc2.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/myatc2m.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/myatc3.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/myatc3m.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mycom0.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mycom0m.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mycom1.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mycom1m.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mycom2.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mycom2m.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mydm0.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mydm0m.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mydm1.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mydm1m.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mydm2.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mydm2m.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mysasi.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mynage.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/jp_my0s.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/jp_my1s.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/my_my0s.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/my_my1s.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/hr_my0.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/myido0.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/myido1.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mytos0.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mytos1.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mytos2.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mkbks.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mycyg.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/nj_jp0.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/nj_my0.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/32ftb0.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/32ftb1.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mytb0.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/mytb1.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/kgatc1.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/kgatc2.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/kgcomb0.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/kgcomb0m.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/kgcomb1.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/kgcomb1m.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/kgcomb2.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/kgcomb2m.lz \
		$(MIYAMA_DIR)\$(ANM_DIR)/my_at0.lz
	hdlink /n /l my.lis

$(MIYAMA_DIR)\$(ANM_DIR)/myiki.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn myiki
	cmplz myiki.mtn myiki.lz
	cd ..\..

$(MYTOB_DIR)\$(ANM_DIR)/mytb0.lz:
	cd $(MYTOB_DIR)\$(ANM_DIR)
	bin2mtn mytb0
	cmplz mytb0.mtn mytb0.lz
	cd ..\..

$(MYTOB_DIR)\$(ANM_DIR)/mytb1.lz:
	cd $(MYTOB_DIR)\$(ANM_DIR)
	bin2mtn mytb1
	cmplz mytb1.mtn mytb1.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mycom0.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mycom0
	cmplz mycom0.mtn mycom0.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mycom0m.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mycom0m
	cmplz mycom0m.mtn mycom0m.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mycom1.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mycom1
	cmplz mycom1.mtn mycom1.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mycom1m.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mycom1m
	cmplz mycom1m.mtn mycom1m.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mycom2.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mycom2
	cmplz mycom2.mtn mycom2.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mycom2m.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mycom2m
	cmplz mycom2m.mtn mycom2m.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mydm0.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mydm0
	cmplz mydm0.mtn mydm0.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mydm0m.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mydm0m
	cmplz mydm0m.mtn mydm0m.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mydm1.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mydm1
	cmplz mydm1.mtn mydm1.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mydm1m.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mydm1m
	cmplz mydm1m.mtn mydm1m.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mydm2.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mydm2
	cmplz mydm2.mtn mydm2.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mydm2m.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mydm2m
	cmplz mydm2m.mtn mydm2m.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mysasi.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mysasi
	cmplz mysasi.mtn mysasi.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mynage.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mynage
	cmplz mynage.mtn mynage.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/jp_my0s.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn jp_my0s
	cmplz jp_my0s.mtn jp_my0s.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/jp_my1s.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn jp_my1s
	cmplz jp_my1s.mtn jp_my1s.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/myido0.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn myido0
	cmplz myido0.mtn myido0.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/myido1.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn myido1
	cmplz myido1.mtn myido1.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mytos0.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mytos0
	cmplz mytos0.mtn mytos0.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mytos1.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mytos1
	cmplz mytos1.mtn mytos1.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mytos2.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mytos2
	cmplz mytos2.mtn mytos2.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mkbks.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mkbks
	cmplz mkbks.mtn mkbks.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mycyg.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mycyg
	cmplz mycyg.mtn mycyg.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/my_my0s.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn my_my0s
	cmplz my_my0s.mtn my_my0s.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/my_my1s.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn my_my1s
	cmplz my_my1s.mtn my_my1s.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/hr_my0.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn hr_my0
	cmplz hr_my0.mtn hr_my0.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/myatc2.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn myatc2
	cmplz myatc2.mtn myatc2.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/myatc2m.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn myatc2m
	cmplz myatc2m.mtn myatc2m.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/myatc3.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn myatc3
	cmplz myatc3.mtn myatc3.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/myatc3m.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn myatc3m
	cmplz myatc3m.mtn myatc3m.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/nj_jp0.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn nj_jp0
	cmplz nj_jp0.mtn nj_jp0.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/nj_my0.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn nj_my0
	cmplz nj_my0.mtn nj_my0.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/my_at0.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn my_at0
	cmplz my_at0.mtn my_at0.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/32ftb0.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn 32ftb0
	cmplz 32ftb0.mtn 32ftb0.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/32ftb1.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn 32ftb1
	cmplz 32ftb1.mtn 32ftb1.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mytb0.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mytb0
	cmplz mytb0.mtn mytb0.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/mytb1.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn mytb1
	cmplz mytb1.mtn mytb1.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/kgatc1.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn kgatc1
	cmplz kgatc1.mtn kgatc1.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/kgatc2.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn kgatc2
	cmplz kgatc2.mtn kgatc2.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/kgcomb0.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn kgcomb0
	cmplz kgcomb0.mtn kgcomb0.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/kgcomb0m.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn kgcomb0m
	cmplz kgcomb0m.mtn kgcomb0m.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/kgcomb1.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn kgcomb1
	cmplz kgcomb1.mtn kgcomb1.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/kgcomb1m.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn kgcomb1m
	cmplz kgcomb1m.mtn kgcomb1m.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/kgcomb2.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn kgcomb2
	cmplz kgcomb2.mtn kgcomb2.lz
	cd ..\..

$(MIYAMA_DIR)\$(ANM_DIR)/kgcomb2m.lz:
	cd $(MIYAMA_DIR)\$(ANM_DIR)
	bin2mtn kgcomb2m
	cmplz kgcomb2m.mtn kgcomb2m.lz
	cd ..\..

