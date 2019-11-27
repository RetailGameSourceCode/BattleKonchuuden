ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
PN_DIR=18\rsd
PNTOBI_DIR=18tob\rsd

all : pn.mot pn1.mod pn2.mod
    psymake

pn1.mod: $(PN_DIR)\pn1.lz $(PNTOBI_DIR)\pntob1.lz
	hdlink /n /l pn1.lis

$(PN_DIR)\pn1.lz:
	cd $(PN_DIR)
	timpos $(TIM_DIR)/doutai.tim  320   0  16 482
	timpos $(TIM_DIR)/syokaku.tim 366   0  32 482
	timpos $(TIM_DIR)/hige.tim    366  56  48 482
	timpos $(TIM_DIR)/hara2.tim   384   0  64 482
	timpos $(TIM_DIR)/hara1.tim   384  72  80 482
	timpos $(TIM_DIR)/medama.tim  422   0  96 482
	timpos $(TIM_DIR)/head.tim    422  48 112 482
	timpos $(TIM_DIR)/headura.tim 422 144 128 482
	timpos $(TIM_DIR)/tono.tim    502   0 144 482
	rsdlink pniki.arg
	tmdsort -o pn1.tmd a.tmd
	cmplz pn1.tmd pn1.lz
	del a.tmd
	cd ..\..

$(PNTOBI_DIR)\pntob1.lz:
	cd $(PNTOBI_DIR)
	timpos $(TIM_DIR)/doutai.tim  320   0  16 482
	timpos $(TIM_DIR)/syokaku.tim 366   0  32 482
	timpos $(TIM_DIR)/hige.tim    366  56  48 482
	timpos $(TIM_DIR)/hane1.tim   366  80 160 482
	timpos $(TIM_DIR)/hara2.tim   384   0  64 482
	timpos $(TIM_DIR)/hara1.tim   384  72  80 482
	timpos $(TIM_DIR)/medama.tim  422   0  96 482
	timpos $(TIM_DIR)/head.tim    422  48 112 482
	timpos $(TIM_DIR)/headura.tim 422 144 128 482
	timpos $(TIM_DIR)/hara4.tim   448   0 176 482
	timpos $(TIM_DIR)/hane2.tim   464   0 192 482
	timpos $(TIM_DIR)/tono.tim    502   0 144 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name18.tim     896   0   0 487
	timpos $(NAMEVS)/namevs18.tim 896  16  16 487
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/medama.tim  medama.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/tono.tim    tono.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name18.tim     name.lz
	cmplz $(NAMEVS)/namevs18.tim namevs.lz
	hdlink /n /l ..\..\pn1t.lis
	rsdlink pntobi.arg
	tmdsort -o pntob1.tmd a.tmd
	cmplz pntob1.tmd pntob1.lz
	del a.tmd
	cd ..\..

pn2.mod: $(PN_DIR)\pn2.lz $(PNTOBI_DIR)\pntob2.lz
	hdlink /n /l pn2.lis

$(PN_DIR)\pn2.lz:
	cd $(PN_DIR)
	timpos $(TIM_DIR)/doutai.tim  576   0  16 490
	timpos $(TIM_DIR)/syokaku.tim 622   0  32 490
	timpos $(TIM_DIR)/hige.tim    622  56  48 490
	timpos $(TIM_DIR)/hara2.tim   640   0  64 490
	timpos $(TIM_DIR)/hara1.tim   640  72  80 490
	timpos $(TIM_DIR)/medama.tim  678   0  96 490
	timpos $(TIM_DIR)/head.tim    678  48 112 490
	timpos $(TIM_DIR)/headura.tim 678 144 128 490
	timpos $(TIM_DIR)/tono.tim    758   0 144 490
	rsdlink pniki.arg
	tmdsort -o pn2.tmd a.tmd
	cmplz pn2.tmd pn2.lz
	del a.tmd
	cd ..\..

$(PNTOBI_DIR)\pntob2.lz:
	cd $(PNTOBI_DIR)
	timpos $(TIM_DIR)/doutai.tim  576   0  16 490
	timpos $(TIM_DIR)/syokaku.tim 622   0  32 490
	timpos $(TIM_DIR)/hige.tim    622  56  48 490
	timpos $(TIM_DIR)/hane1.tim   622  80 160 490
	timpos $(TIM_DIR)/hara2.tim   640   0  64 490
	timpos $(TIM_DIR)/hara1.tim   640  72  80 490
	timpos $(TIM_DIR)/medama.tim  678   0  96 490
	timpos $(TIM_DIR)/head.tim    678  48 112 490
	timpos $(TIM_DIR)/headura.tim 678 144 128 490
	timpos $(TIM_DIR)/hara4.tim   704   0 176 490
	timpos $(TIM_DIR)/hane2.tim   720   0 192 490
	timpos $(TIM_DIR)/tono.tim    758   0 144 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name18.tim     926   0   0 495
	timpos $(NAMEVS)/namevs18.tim 896  56  16 495
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/medama.tim  medama.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/tono.tim    tono.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name18.tim     name.lz
	cmplz $(NAMEVS)/namevs18.tim namevs.lz
	hdlink /n /l ..\..\pn2t.lis
	rsdlink pntobi.arg
	tmdsort -o pntob2.tmd a.tmd
	cmplz pntob2.tmd pntob2.lz
	del a.tmd
	cd ..\..

pn.mot:
	hdlink /n /l pn.lis

