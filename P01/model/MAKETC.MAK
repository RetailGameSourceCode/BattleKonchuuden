ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
KUMO_DIR=53\rsd

all : tc.mot tc1.mod tc2.mod
    psymake

tc1.mod: $(KUMO_DIR)\tc1.lz
	hdlink /n /l tc1.lis

$(KUMO_DIR)\tc1.lz:
	cd $(KUMO_DIR)
	timpos $(TIM_DIR)/ke2.tim     320   0  16 482
	timpos $(TIM_DIR)/hara.tim    320  64  32 482
	timpos $(TIM_DIR)/ke3.tim     352  64  48 482
	timpos $(TIM_DIR)/doutai.tim  384   0  64 482
	timpos $(TIM_DIR)/ke4.tim     502   0  80 482
	timpos $(TIM_DIR)/ke.tim      502  32  96 482
	timpos $(TIM_DIR)/ke5.tim     502  64 112 482
	timpos $(TIM_DIR)/leg.tim     502  96 128 482
	timpos $(TIM_DIR)/leg2.tim    502 128 144 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name53.tim     896   0   0 487
	timpos $(NAMEVS)/namevs53.tim 896  16  16 487
	cmplz $(TIM_DIR)/ke2.tim     ke2.lz
	cmplz $(TIM_DIR)/hara.tim    hara.lz
	cmplz $(TIM_DIR)/ke3.tim     ke3.lz
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/ke4.tim     ke4.lz
	cmplz $(TIM_DIR)/ke.tim      ke.lz
	cmplz $(TIM_DIR)/ke5.tim     ke5.lz
	cmplz $(TIM_DIR)/leg.tim     leg.lz
	cmplz $(TIM_DIR)/leg2.tim    leg2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name53.tim     name.lz
	cmplz $(NAMEVS)/namevs53.tim namevs.lz
	hdlink /n /l ..\..\tc1t.lis
	rsdlink kmoiki.arg
	tmdsort -o tc1.tmd a.tmd
	cmplz tc1.tmd tc1.lz
	del a.tmd
	cd ..\..

tc2.mod: $(KUMO_DIR)\tc2.lz
	hdlink /n /l tc2.lis

$(KUMO_DIR)\tc2.lz:
	cd $(KUMO_DIR)
	timpos $(TIM_DIR)/ke2.tim     576   0  16 490
	timpos $(TIM_DIR)/hara.tim    576  64  32 490
	timpos $(TIM_DIR)/ke3.tim     608  64  48 490
	timpos $(TIM_DIR)/doutai.tim  640   0  64 490
	timpos $(TIM_DIR)/ke4.tim     758   0  80 490
	timpos $(TIM_DIR)/ke.tim      758  32  96 490
	timpos $(TIM_DIR)/ke5.tim     758  64 112 490
	timpos $(TIM_DIR)/leg.tim     758  96 128 490
	timpos $(TIM_DIR)/leg2.tim    758 128 144 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name53.tim     926   0   0 495
	timpos $(NAMEVS)/namevs53.tim 896  56  16 495
	cmplz $(TIM_DIR)/ke2.tim     ke2.lz
	cmplz $(TIM_DIR)/hara.tim    hara.lz
	cmplz $(TIM_DIR)/ke3.tim     ke3.lz
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/ke4.tim     ke4.lz
	cmplz $(TIM_DIR)/ke.tim      ke.lz
	cmplz $(TIM_DIR)/ke5.tim     ke5.lz
	cmplz $(TIM_DIR)/leg.tim     leg.lz
	cmplz $(TIM_DIR)/leg2.tim    leg2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name53.tim     name.lz
	cmplz $(NAMEVS)/namevs53.tim namevs.lz
	hdlink /n /l ..\..\tc2t.lis
	rsdlink kmoiki.arg
	tmdsort -o tc2.tmd a.tmd
	cmplz tc2.tmd tc2.lz
	del a.tmd
	cd ..\..

tc.mot: $(KUMO_DIR)\$(ANM_DIR)/kmoiki.lz \
		$(KUMO_DIR)\$(ANM_DIR)/jp_km0.lz \
		$(KUMO_DIR)\$(ANM_DIR)/jp_km1.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmatc1.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmatc2.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmbks.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmchag.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmcom0.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmcom0m.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmcom1.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmcom1m.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmcom2.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmcom2m.lz \
		$(KUMO_DIR)\$(ANM_DIR)/hm_km.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmdmg0.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmdmg0m.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmdmg1.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmdmg1m.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmdmg2.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmdmg2m.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmftb0.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmftb1.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmido0.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmido1.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmtame.lz \
		$(KUMO_DIR)\$(ANM_DIR)/my_km0.lz \
		$(KUMO_DIR)\$(ANM_DIR)/my_km1.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kma2dmg.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kma2uke.lz \
		$(KUMO_DIR)\$(ANM_DIR)/kmyoke.lz \
		$(KUMO_DIR)\$(ANM_DIR)/53tos0.lz \
		$(KUMO_DIR)\$(ANM_DIR)/53tos1.lz \
		$(KUMO_DIR)\$(ANM_DIR)/53tos2.lz \
		$(KUMO_DIR)\$(ANM_DIR)/02_530s.lz
	hdlink /n /l tc.lis

$(KUMO_DIR)\$(ANM_DIR)/kmoiki.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmoiki
	cmplz kmoiki.mtn kmoiki.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/jp_km0.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn jp_km0
	cmplz jp_km0.mtn jp_km0.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/jp_km1.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn jp_km1
	cmplz jp_km1.mtn jp_km1.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmatc1.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmatc1
	cmplz kmatc1.mtn kmatc1.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmatc2.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmatc2
	cmplz kmatc2.mtn kmatc2.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmbks.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmbks
	cmplz kmbks.mtn kmbks.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmchag.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmchag
	cmplz kmchag.mtn kmchag.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmcom0.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmcom0
	cmplz kmcom0.mtn kmcom0.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmcom0m.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmcom0m
	cmplz kmcom0m.mtn kmcom0m.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmcom1.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmcom1
	cmplz kmcom1.mtn kmcom1.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmcom1m.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmcom1m
	cmplz kmcom1m.mtn kmcom1m.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmcom2.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmcom2
	cmplz kmcom2.mtn kmcom2.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmcom2m.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmcom2m
	cmplz kmcom2m.mtn kmcom2m.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/hm_km.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn hm_km
	cmplz hm_km.mtn hm_km.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmdmg0.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmdmg0
	cmplz kmdmg0.mtn kmdmg0.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmdmg0m.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmdmg0m
	cmplz kmdmg0m.mtn kmdmg0m.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmdmg1.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmdmg1
	cmplz kmdmg1.mtn kmdmg1.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmdmg1m.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmdmg1m
	cmplz kmdmg1m.mtn kmdmg1m.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmdmg2.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmdmg2
	cmplz kmdmg2.mtn kmdmg2.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmdmg2m.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmdmg2m
	cmplz kmdmg2m.mtn kmdmg2m.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmftb0.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmftb0
	cmplz kmftb0.mtn kmftb0.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmftb1.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmftb1
	cmplz kmftb1.mtn kmftb1.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmido0.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmido0
	cmplz kmido0.mtn kmido0.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmido1.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmido1
	cmplz kmido1.mtn kmido1.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmtame.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmtame
	cmplz kmtame.mtn kmtame.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/my_km0.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn my_km0
	cmplz my_km0.mtn my_km0.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/my_km1.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn my_km1
	cmplz my_km1.mtn my_km1.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/02_530s.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn 02_530s
	cmplz 02_530s.mtn 02_530s.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kma2dmg.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kma2dmg
	cmplz kma2dmg.mtn kma2dmg.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kma2uke.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kma2uke
	cmplz kma2uke.mtn kma2uke.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/kmyoke.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn kmyoke
	cmplz kmyoke.mtn kmyoke.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/53tos0.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn 53tos0
	cmplz 53tos0.mtn 53tos0.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/53tos1.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn 53tos1
	cmplz 53tos1.mtn 53tos1.lz
	cd ..\..

$(KUMO_DIR)\$(ANM_DIR)/53tos2.lz:
	cd $(KUMO_DIR)\$(ANM_DIR)
	bin2mtn 53tos2
	cmplz 53tos2.mtn 53tos2.lz
	cd ..\..




