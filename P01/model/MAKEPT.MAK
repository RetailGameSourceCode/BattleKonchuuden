ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
PT_DIR=17\rsd
PTTOBI_DIR=17tob\rsd

all : pt.mot pt1.mod pt2.mod
    psymake

pt1.mod: $(PT_DIR)\pt1.lz $(PTTOBI_DIR)\pttob1.lz
	hdlink /n /l pt1.lis

$(PT_DIR)\pt1.lz:
	cd $(PT_DIR)
	timpos $(TIM_DIR)/doutai.tim  320   0  16 482
	timpos $(TIM_DIR)/syokaku.tim 366   0  32 482
	timpos $(TIM_DIR)/hige.tim    366  56  48 482
	timpos $(TIM_DIR)/ohige2.tim  366  80 160 482
	timpos $(TIM_DIR)/ohige3.tim  374  80 176 482
	timpos $(TIM_DIR)/me.tim      366 144 192 482
	timpos $(TIM_DIR)/tono.tim    366 192 144 482
	timpos $(TIM_DIR)/headura.tim 384   0 128 482
	timpos $(TIM_DIR)/hara1.tim   384  96  80 482
	timpos $(TIM_DIR)/head.tim    406   0 112 482
	timpos $(TIM_DIR)/hara2.tim   448   0  64 482
	timpos $(TIM_DIR)/ohige.tim   448  72  96 482
	rsdlink psiki.arg
	tmdsort -o pt1.tmd a.tmd
	cmplz pt1.tmd pt1.lz
	del a.tmd
	cd ..\..

$(PTTOBI_DIR)\pttob1.lz:
	cd $(PTTOBI_DIR)
	timpos $(TIM_DIR)/doutai.tim  320   0  16 482
	timpos $(TIM_DIR)/syokaku.tim 366   0  32 482
	timpos $(TIM_DIR)/hige.tim    366  56  48 482
	timpos $(TIM_DIR)/ohige2.tim  366  80 160 482
	timpos $(TIM_DIR)/ohige3.tim  374  80 176 482
	timpos $(TIM_DIR)/me.tim      366 144 192 482
	timpos $(TIM_DIR)/tono.tim    366 192 144 482
	timpos $(TIM_DIR)/headura.tim 384   0 128 482
	timpos $(TIM_DIR)/hara1.tim   384  96  80 482
	timpos $(TIM_DIR)/head.tim    406   0 112 482
	timpos $(TIM_DIR)/hane2.tim   420 192 208 482
	timpos $(TIM_DIR)/hara4.tim   430   0 224 482
	timpos $(TIM_DIR)/hara2.tim   448   0  64 482
	timpos $(TIM_DIR)/ohige.tim   448  72  96 482
	timpos $(TIM_DIR)/hane1.tim   484 128 240 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name17.tim     896   0   0 487
	timpos $(NAMEVS)/namevs17.tim 896  16  16 487
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/ohige2.tim  ohige2.lz
	cmplz $(TIM_DIR)/ohige3.tim  ohige3.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/tono.tim    tono.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/ohige.tim   ohige.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name17.tim     name.lz
	cmplz $(NAMEVS)/namevs17.tim namevs.lz
	hdlink /n /l ..\..\pt1t.lis
	rsdlink pstobi.arg
	tmdsort -o pttob1.tmd a.tmd
	cmplz pttob1.tmd pttob1.lz
	del a.tmd
	cd ..\..

pt2.mod: $(PT_DIR)\pt2.lz $(PTTOBI_DIR)\pttob2.lz
	hdlink /n /l pt2.lis

$(PT_DIR)\pt2.lz:
	cd $(PT_DIR)
	timpos $(TIM_DIR)/doutai.tim  576   0  16 490
	timpos $(TIM_DIR)/syokaku.tim 622   0  32 490
	timpos $(TIM_DIR)/hige.tim    622  56  48 490
	timpos $(TIM_DIR)/ohige2.tim  622  80 160 490
	timpos $(TIM_DIR)/ohige3.tim  630  80 176 490
	timpos $(TIM_DIR)/me.tim      622 144 192 490
	timpos $(TIM_DIR)/tono.tim    622 192 144 490
	timpos $(TIM_DIR)/headura.tim 640   0 128 490
	timpos $(TIM_DIR)/hara1.tim   640  96  80 490
	timpos $(TIM_DIR)/head.tim    662   0 112 490
	timpos $(TIM_DIR)/hara2.tim   704   0  64 490
	timpos $(TIM_DIR)/ohige.tim   704  72  96 490
	rsdlink psiki.arg
	tmdsort -o pt2.tmd a.tmd
	cmplz pt2.tmd pt2.lz
	del a.tmd
	cd ..\..

$(PTTOBI_DIR)\pttob2.lz:
	cd $(PTTOBI_DIR)
	timpos $(TIM_DIR)/doutai.tim  576   0  16 490
	timpos $(TIM_DIR)/syokaku.tim 622   0  32 490
	timpos $(TIM_DIR)/hige.tim    622  56  48 490
	timpos $(TIM_DIR)/ohige2.tim  622  80 160 490
	timpos $(TIM_DIR)/ohige3.tim  630  80 176 490
	timpos $(TIM_DIR)/me.tim      622 144 192 490
	timpos $(TIM_DIR)/tono.tim    622 192 144 490
	timpos $(TIM_DIR)/headura.tim 640   0 128 490
	timpos $(TIM_DIR)/hara1.tim   640  96  80 490
	timpos $(TIM_DIR)/head.tim    662   0 112 490
	timpos $(TIM_DIR)/hane2.tim   676 192 208 490
	timpos $(TIM_DIR)/hara4.tim   686   0 224 490
	timpos $(TIM_DIR)/hara2.tim   704   0  64 490
	timpos $(TIM_DIR)/ohige.tim   704  72  96 490
	timpos $(TIM_DIR)/hane1.tim   740 128 240 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name17.tim     926   0   0 495
	timpos $(NAMEVS)/namevs17.tim 896  56  16 495
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/ohige2.tim  ohige2.lz
	cmplz $(TIM_DIR)/ohige3.tim  ohige3.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/tono.tim    tono.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/ohige.tim   ohige.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name17.tim     name.lz
	cmplz $(NAMEVS)/namevs17.tim namevs.lz
	hdlink /n /l ..\..\pt2t.lis
	rsdlink pstobi.arg
	tmdsort -o pttob2.tmd a.tmd
	cmplz pttob2.tmd pttob2.lz
	del a.tmd
	cd ..\..

pt.mot:
	hdlink /n /l pt.lis

