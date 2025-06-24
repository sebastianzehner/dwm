/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 6;        /* 2 is the default spacing around the bar's font */
static const char *fonts[]          = { "CaskaydiaCove Nerd Font:size=14" };
static const char dmenufont[]       =   "CaskaydiaCove Nerd Font:size=14";

/* colorscheme catppuccin mocha */
static char normbgcolor[]           = "#11111b"; /* Crust     */
static char normbordercolor[]       = "#1e1e2e"; /* Base      */
static char normfgcolor[]           = "#a6adc8"; /* Subtext 0 */
static char selfgcolor[]            = "#cdd6f4"; /* Text      */
static char selbordercolor[]        = "#11111b"; /* Crust     */
static char selbgcolor[]            = "#1e1e2e"; /* Base      */
static char col1[]                  = "#f38ba8"; /* Red       */
static char col2[]                  = "#a6e3a1"; /* Green     */
static char col3[]                  = "#f9e2af"; /* Yellow    */
static char col4[]                  = "#89b4fa"; /* Blue      */
static char col5[]                  = "#f5c2e7"; /* Pink      */
static char col6[]                  = "#94e2d5"; /* Teal      */

enum  { SchemeNorm, SchemeCol1, SchemeCol2, SchemeCol3, SchemeCol4,
        SchemeCol5, SchemeCol6, SchemeSel };  /* color schemes */

static char *colors[][3] = {
      /*                fg           bg           border     */
      [SchemeNorm]  = { normfgcolor, normbgcolor, normbordercolor },
      [SchemeCol1]  = { col1,        normbgcolor, normbordercolor },
      [SchemeCol2]  = { col2,        normbgcolor, normbordercolor },
      [SchemeCol3]  = { col3,        normbgcolor, normbordercolor },
      [SchemeCol4]  = { col4,        normbgcolor, normbordercolor },
      [SchemeCol5]  = { col5,        normbgcolor, normbordercolor },
      [SchemeCol6]  = { col6,        normbgcolor, normbordercolor },
      [SchemeSel]   = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "󰍳" };
static const int taglayouts[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static const Rule rules[] = {
      /* xprop(1):
      *	WM_CLASS(STRING) = instance, class
      *	WM_NAME(STRING) = title
      */
      /* class     	      instance  title           tags mask  isfloating  isterminal   noswallow  monitor   border width */
      { "Gimp",           NULL,     NULL,           0,         1,          0,           0,        -1,        -1 },
      { "firefox-esr", 	  NULL,     NULL,           0,         0,          0,          -1,        -1,        0 },
      { "librewolf",   	  NULL,     NULL,           0,         0,          0,          -1,        -1,        0 },
      { "st",             NULL,     NULL,           0,         0,          1,           0,        -1,        -1 },
      { "Minecraft",      NULL,     NULL,           1 << 8,    1,          0,           0,        -1,        0 },
      { "PrismLauncher",  NULL,     NULL,           1 << 8,    1,          0,           0,        -1,        0 },
      { NULL,             NULL,     "Event Tester", 0,         0,          0,           1,        -1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     	= 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     	= 1;    /* number of clients in master area */
static const int resizehints 	= 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; 	/* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
      /* symbol     arrange function */
      { "[]=",      tile },    /* first entry is default [options from 0 to 12] */
      { "[M]",      monocle },
      { "[@]",      spiral },
      { "[\\]",     dwindle },
      { "H[]",      deck },
      { "TTT",      bstack },
      { "===",      bstackhoriz },
      { "HHH",      grid },
      { "###",      nrowgrid },
      { "---",      horizgrid },
      { ":::",      gaplessgrid },
      { "|M|",      centeredmaster },
      { ">M>",      centeredfloatingmaster },
      { "><>",      NULL },    /* no layout function means floating behavior */
      { NULL,       NULL },
};

/* key definitions */
#include <X11/XF86keysym.h>
#define MODKEY Mod1Mask
#define MODKEY2 Mod4Mask
#define TAGKEYS(KEY,TAG) \
      { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
      { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
      { MODKEY2,                      KEY,      tag,            {.ui = 1 << TAG} }, \
      { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "st", NULL };

static const Key keys[] = {
      /* modifier                     key                       function        argument */
      { MODKEY,                       XK_space,                 spawn,          {.v = dmenucmd } },
      { MODKEY|ShiftMask,             XK_Return,                spawn,          {.v = termcmd } },
      { MODKEY,                       XK_b,                     togglebar,      {0} },
      { MODKEY,                       XK_j,                     focusstack,     {.i = +1 } },
      { MODKEY,                       XK_k,                     focusstack,     {.i = -1 } },
      { MODKEY,                       XK_i,                     incnmaster,     {.i = +1 } },
      { MODKEY,                       XK_d,                     incnmaster,     {.i = -1 } },
      { MODKEY,                       XK_h,                     setmfact,       {.f = -0.05} },
      { MODKEY,                       XK_l,                     setmfact,       {.f = +0.05} },
      { MODKEY,                       XK_Return,                zoom,           {0} },
      { MODKEY|Mod4Mask,              XK_u,                     incrgaps,       {.i = +1 } },
      { MODKEY|Mod4Mask|ShiftMask,    XK_u,                     incrgaps,       {.i = -1 } },
      { MODKEY|Mod4Mask,              XK_i,                     incrigaps,      {.i = +1 } },
      { MODKEY|Mod4Mask|ShiftMask,    XK_i,                     incrigaps,      {.i = -1 } },
      { MODKEY|Mod4Mask,              XK_o,                     incrogaps,      {.i = +1 } },
      { MODKEY|Mod4Mask|ShiftMask,    XK_o,                     incrogaps,      {.i = -1 } },
      { MODKEY|Mod4Mask,              XK_6,                     incrihgaps,     {.i = +1 } },
      { MODKEY|Mod4Mask|ShiftMask,    XK_6,                     incrihgaps,     {.i = -1 } },
      { MODKEY|Mod4Mask,              XK_7,                     incrivgaps,     {.i = +1 } },
      { MODKEY|Mod4Mask|ShiftMask,    XK_7,                     incrivgaps,     {.i = -1 } },
      { MODKEY|Mod4Mask,              XK_8,                     incrohgaps,     {.i = +1 } },
      { MODKEY|Mod4Mask|ShiftMask,    XK_8,                     incrohgaps,     {.i = -1 } },
      { MODKEY|Mod4Mask,              XK_9,                     incrovgaps,     {.i = +1 } },
      { MODKEY|Mod4Mask|ShiftMask,    XK_9,                     incrovgaps,     {.i = -1 } },
      { MODKEY|Mod4Mask,              XK_0,                     togglegaps,     {0} },
      { MODKEY|Mod4Mask|ShiftMask,    XK_0,                     defaultgaps,    {0} },
      { MODKEY,                       XK_Tab,                   view,           {0} },
      { MODKEY|ShiftMask,             XK_c,                     killclient,     {0} },
      { MODKEY2,                      XK_q,                     killclient,     {0} },
      { MODKEY,                       XK_t,                     setlayout,      {.v = &layouts[0]} },
      { MODKEY,                       XK_f,                     setlayout,      {.v = &layouts[1]} },
      { MODKEY,                       XK_g,                     setlayout,      {.v = &layouts[7]} },
      { MODKEY,                       XK_m,                     setlayout,      {.v = &layouts[2]} },
      { MODKEY,                       XK_n,                     setlayout,      {.v = &layouts[8]} },
      { MODKEY,                       XK_p,                     setlayout,      {.v = 0} },
      { MODKEY|ShiftMask,             XK_space,                 togglefloating, {0} },
      { MODKEY,                       XK_0,                     view,           {.ui = ~0 } },
      { MODKEY|ShiftMask,             XK_0,                     tag,            {.ui = ~0 } },
      { MODKEY,                       XK_comma,                 focusmon,       {.i = -1 } },
      { MODKEY,                       XK_period,                focusmon,       {.i = +1 } },
      { MODKEY|ShiftMask,             XK_comma,                 tagmon,         {.i = -1 } },
      { MODKEY|ShiftMask,             XK_period,                tagmon,         {.i = +1 } },
      { MODKEY,                       XK_F5,                    xrdb,           {.v = NULL } },
      { MODKEY2,                      XK_Tab,                   viewnext,       {0} },
      { MODKEY2,                      XK_Right,                 viewnext,       {0} },
      { MODKEY2,                      XK_Left,                  viewprev,       {0} },
      { MODKEY2|ShiftMask,            XK_Right,                 tagtonext,      {0} },
      { MODKEY2|ShiftMask,            XK_Left,                  tagtoprev,      {0} },
      TAGKEYS(                        XK_1,                      0)
      TAGKEYS(                        XK_2,                      1)
      TAGKEYS(                        XK_3,                      2)
      TAGKEYS(                        XK_4,                      3)
      TAGKEYS(                        XK_5,                      4)
      TAGKEYS(                        XK_6,                      5)
      TAGKEYS(                        XK_7,                      6)
      TAGKEYS(                        XK_8,                      7)
      TAGKEYS(                        XK_9,                      8)
      { MODKEY|ShiftMask,             XK_q,                     quit,           {0} },

/* multimedia keys */
      { 0,                            XF86XK_AudioRaiseVolume,  spawn,          SHCMD("audio_volume up") },
      { 0,                            XF86XK_AudioLowerVolume,  spawn,          SHCMD("audio_volume down") },
      { 0,                            XF86XK_AudioMute,         spawn,          SHCMD("audio_volume mute") },

/* script launch bindings */
      { MODKEY,                       XK_v,                     spawn,          {.v = (const char*[]){ "cliphist", "sel", NULL } } },
      { MODKEY,                       XK_c,                     spawn,          {.v = (const char*[]){ "cliphist", "add", NULL } } },
      { MODKEY,                       XK_q,                     spawn,          {.v = (const char*[]){ "powermenu", NULL } } },
      { MODKEY|ShiftMask,             XK_3,                     spawn,          SHCMD("screenshot full") },
      { MODKEY|ShiftMask,             XK_4,                     spawn,          SHCMD("screenshot area") },
      { MODKEY|ShiftMask,             XK_5,                     spawn,          SHCMD("screenshot") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
      /* click                event mask      button          function        argument */
      { ClkLtSymbol,          0,              Button1,        setlayout,      {.v = &layouts[0]} },
      { ClkLtSymbol,          0,              Button2,        setlayout,      {.v = &layouts[8]} },
      { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = 0} },
      { ClkWinTitle,          0,              Button2,        zoom,           {0} },
      { ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
      { ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
      { ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
      { ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
      { ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
      { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
      { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
      { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
      { ClkTagBar,            0,              Button1,        view,           {0} },
      { ClkTagBar,            0,              Button3,        toggleview,     {0} },
      { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
      { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signum>"` */
static Signal signals[] = {
      /* signum       function        argument  */
      { 1,            setlayout,      {.v = 0} },
      { 2,            xrdb,           {.v = NULL} },
};
