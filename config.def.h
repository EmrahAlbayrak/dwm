#include <X11/XF86keysym.h>
/* Appearance */
static const unsigned int borderpx     = 2; /* border pixel of windows */
static const unsigned int gappx        = 4; /* gaps between windows */
static const unsigned int snap         = 1; /* snap pixel */
static const unsigned int titleScheme  = 1; /* Use Normal/Title scheme for title*/
static const unsigned int hInd         = 2; /* Current tag indicator height */
static const unsigned int maxMaster    = 2; /* Maximum allowed master count */
static const int showbar               = 1; /* 0 means no bar */
static const int topbar                = 1; /* 0 means bottom bar */
static const int horizpadbar           = 0; /* horizontal padding for statusbar */
static const int vertpadbar            = 6; /* vertical padding for statusbar */
static const char iconMenu[]           = "";
static const char iconClose[]          = "";
/* Colors */
static const char col0[] = "#000000";
static const char col1[] = "#8B909F";
static const char col2[] = "#3F4457";
static const char col3[] = "#FFFFFF";
static const char col4[] = "#5F657B";
static const char col5[] = "#EC6F2D";
static const char col6[] = "#303030";
static const int  alpha  = 180;
/* Colors */
static const char nb[] = "#000000";
static const char sb[] = "#303030";
static const char nf[] = "#606060";
static const char sf[] = "#FFFFFF";
/* Fonts */
static const char dmenufont[]   = "Liberation Mono:Regular:size=12";
static const char *fonts[]      =
{
    "Liberation Mono:Regular:size=8",
    "FontAwesome:Regular:size=7"
};

/* Colorschemes */
static const char *colors[][3] =
{
    /*                  fg      bg      border  */
    [SchemeNorm]    = { col1,   col0,   col6    },
    [SchemeSel]     = { col1,   col0,   col5    },
    [SchemeTitle]   = { col4,   col0,   0       },
    [SchemeInd]     = { col5,   0,      0       },
    [SchemeBtn]     = { col5,   col0,   0       }
};

/* Alphas */
static const unsigned int alphas[][3] =
{
    /*                  fg      bg      border  */
    [SchemeNorm]    = { OPAQUE, alpha,  OPAQUE  },
    [SchemeTitle]   = { OPAQUE, alpha,  OPAQUE  },
    [SchemeSel]     = { OPAQUE, alpha,  OPAQUE  },
    [SchemeBtn]     = { OPAQUE, alpha,  OPAQUE  },
    [SchemeInd]     = { OPAQUE, OPAQUE, OPAQUE  },
};

/* tagging */
static const char *tags[] = {"1","2","3","4","5","6","7","8","9"};
/* Rules */
static const Rule rules[] =
{
    /* class			    instance            title                   tags mask   isCentered  isfloating  monitor */
    { "Brave-browser",      NULL,               NULL,                   1,          0,          0,          -1,     },
    { "st-256color",        NULL,               NULL,                   0,          1,          1,          -1,     },
    { "Qalculate-gtk",	    NULL,               NULL,                   0,          1,          1,          -1,     },
    { "Uget-gtk",  		    NULL,               NULL,                   0,          1,          1,          -1,     },
    { NULL,  			    NULL,               "Codeblocks_Terminal",  0,          0,          1,          -1,     },
    { "Soffice",            NULL,               NULL,                   1 << 2,     0,          0,          -1,     },
    { "Transmission-gtk",   NULL,               NULL,                   1 << 7,     0,          0,          -1,     },
    { NULL,  			    NULL,               "VLC media player",     1 << 8,     1,          0,          -1,     },
};

/* Layout(s) */
static const float mfact     = 0.5;  /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] =
{
    /* symbol     arrange function */
    { " M ",      monocle           },
    { " V ",      tile              },    /* first entry is default */
	{ " H ",      bstack            },
    { " F ",      NULL              },    /* no layout function means floating behavior */
    { NULL,       NULL              },
};

/* Key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* Helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Commands */
static const char *cmdUpVol[]       = { "/usr/bin/pactl", "set-sink-volume", "0",
                                        "+5%", NULL };
static const char *cmdDownVol[]     = { "/usr/bin/pactl", "set-sink-volume", "0",
                                        "-5%", NULL };
static const char *cmdMute[]        = { "/usr/bin/pactl", "set-sink-mute", "0",
                                        "toggle", NULL };
static const char *cmdReboot[]      = { "systemctl", "reboot", NULL };
static const char *cmdShutdown[]    = { "systemctl", "poweroff", NULL };
static const char *cmdTerm0[]   	= { "st","-g","110x30", NULL };
static const char *cmdTerm1[]   	= { "gnome-terminal", NULL };
static const char *cmdMenu[]    	= { "bar_menu", NULL };
static const char *cmdBrowser[] 	= { "brave-browser", NULL };
static const char *cmdJ4_dmenu[]   	= { "dmenu_j4", NULL };
static const char *cmdDmenuBrowser[]= { "dmenu_browser", NULL };
static const char *cmdDmenu[]       = { "dmenu_run", "-l", "10", "-fn",
        dmenufont, "-nb", nb, "-nf", nf, "-sb", sb, "-sf", sf, NULL };

static Key keys[] =
{
    /* modifier             key                     function            argument */
    { MODKEY,               XK_m,          			zoom,               {0} },
    { MODKEY,               XK_Tab,        			view,               {0} },
    { MODKEY,               XK_q,          			killclient,         {0} },
    { MODKEY,               XK_f,          			togglefloating,     {0} },
    { MODKEY,               XK_s,                   togglesticky,       {0} },
	{ MODKEY,               XK_BackSpace,           scratchpad_show,    {0} },
	{ MODKEY|ControlMask,   XK_BackSpace,           scratchpad_hide,    {0} },
	{ MODKEY|ShiftMask,     XK_BackSpace,           scratchpad_remove,  {0} },
    { MODKEY,               XK_b,          			togglebar,          {0}          },
    { MODKEY,               XK_j,          			focusstack,         {.i = +1 }   },
    { MODKEY,               XK_k,          			focusstack,         {.i = -1 }   },
    { MODKEY,               XK_h,          			setmfact,           {.f = -0.05} },
    { MODKEY,               XK_l,          			setmfact,           {.f = +0.05} },
    { MODKEY,               XK_0,          			view,               {.ui = ~0 }  },
    { MODKEY,               XK_Left,                shiftview,          {.i = -1 }   },
    { MODKEY,               XK_Right,               shiftview,          {.i = +1 }   },
    { MODKEY,               XK_period,    			cyclelayout,        {.i = +1 }   },
    { MODKEY,               XK_comma,               cyclelayout,        {.i = -1 }   },
    { MODKEY,               XK_g,          			setgaps,            {.i = +1 }   },
    { MODKEY|ShiftMask,     XK_g,          			setgaps,            {.i = -1 }   },
    { MODKEY|ControlMask,   XK_g,          			setgaps,            {.i = 0}     },
    { MODKEY,               XK_i,      				incnmaster,         {.i = 1 }    },
    { MODKEY|ControlMask,   XK_i,      				incnmaster,         {.i = -1 }   },
    { MODKEY|ShiftMask,     XK_q,          			quit,               {0}          },
    { MODKEY|ControlMask,   XK_b,          			spawn,              {.v = cmdBrowser }    },
    { MODKEY,               XK_Return,     			spawn,              {.v = cmdTerm0 }      },
    { MODKEY|ControlMask,   XK_Return,     			spawn,              {.v = cmdTerm1 }      },
    { MODKEY,               XK_p,          			spawn,              {.v = cmdDmenu }      },
    { MODKEY,               XK_o,          			spawn,              {.v = cmdDmenuBrowser}},
    { MODKEY,               XK_d,          			spawn,              {.v = cmdJ4_dmenu }   },
    { MODKEY,               XK_Escape,              spawn,              {.v = cmdMenu }   },
    { MODKEY|ControlMask,   XK_v,      				setlayout,          {.v = &layouts[0]}    },
    { MODKEY|ControlMask,   XK_h,      				setlayout,          {.v = &layouts[1]}    },
    { MODKEY|ControlMask,   XK_m,      				setlayout,          {.v = &layouts[2]}    },
    { MODKEY|ControlMask,   XK_f,      				setlayout,          {.v = &layouts[3]}    },
    { MODKEY|ControlMask,   XK_Home,          		spawn,              {.v = cmdReboot}      },
    { MODKEY|ControlMask,   XK_End,          		spawn,              {.v = cmdShutdown}    },
    { 0,                    XF86XK_AudioRaiseVolume,spawn, 			    {.v = cmdUpVol   }    },
    { 0,                    XF86XK_AudioLowerVolume,spawn, 			    {.v = cmdDownVol }    },
    { 0,                    XF86XK_AudioMute,		spawn, 			    {.v = cmdMute }       },
    /* { MODKEY,            XK_t,      				setlayout,          {.v = &layouts[0]} },
     * { MODKEY,            XK_f,      				setlayout,          {.v = &layouts[1]} },
     * { MODKEY,            XK_m,      				setlayout,          {.v = &layouts[2]} },
     * { MODKEY,            XK_u,                   setlayout,          {.v = &layouts[3]} },
     * { MODKEY|ShiftMask,  XK_0,          			tag,                {.ui = ~0 } },
     * { MODKEY,            XK_space,  				setlayout,          {0} },
     * { MODKEY|ShiftMask,  XK_comma,  				tagmon,             {.i = -1 } },
     * { MODKEY|ShiftMask,  XK_period, 				tagmon,             {.i = +1 } },
     * { MODKEY,            XK_comma,  				focusmon,           {.i = -1 } },
     * { MODKEY,            XK_period, 				focusmon,           {.i = +1 } }, */
    TAGKEYS(                XK_1,                   0)
    TAGKEYS(                XK_2,                   1)
    TAGKEYS(                XK_3,                   2)
    TAGKEYS(                XK_4,                   3)
    TAGKEYS(                XK_5,                   4)
    TAGKEYS(                XK_6,                   5)
    TAGKEYS(                XK_7,                   6)
    TAGKEYS(                XK_8,                   7)
    TAGKEYS(                XK_9,                   8)
};

/* Button definitions
Click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] =
{
    /*  click         mask    button   function        argument        */
    { ClkStatusText,  0,      Button4, spawn,          {.v = cmdUpVol  } },
    { ClkStatusText,  0,      Button5, spawn,          {.v = cmdDownVol} },
    { ClkMenu,        0,      Button1, spawn,	       {.v = cmdMenu } },
    { ClkCloseClient, 0,      Button1, killclient,     {0}        },
    { ClkLtSymbol,    0,      Button1, cyclelayout,    {.i = +1 } },
    { ClkLtSymbol,    0,      Button2, cyclelayout,    {.i = -1 } },
    { ClkWinTitle,    0,      Button2, zoom,           {0}        },
    { ClkWinTitle,    0,      Button4, focusstack,     {.i = +1 } },
    { ClkWinTitle,    0,      Button5, focusstack,     {.i = -1 } },
    { ClkTagBar,      0,      Button4, shiftview,      {.i = +1} },
    { ClkTagBar,      0,      Button5, shiftview,      {.i = -1} },
    { ClkClientWin,   MODKEY, Button1, movemouse,      {0} },
    { ClkClientWin,   MODKEY, Button2, togglefloating, {0} },
    { ClkClientWin,   MODKEY, Button3, resizemouse,    {0} },
    { ClkTagBar,      0,      Button1, view,           {0} },
    { ClkTagBar,      0,      Button3, toggleview,     {0} },
    { ClkTagBar,      MODKEY, Button1, tag,            {0} },
    { ClkTagBar,      MODKEY, Button3, toggletag,      {0} },
};

void setlayoutex(const Arg *arg)
{
    setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void viewex(const Arg *arg)
{
    view(&((Arg) { .ui = 1 << arg->ui }));
}

void viewall(const Arg *arg)
{
    view(&((Arg) { .ui = ~0 }));
}

void toggleviewex(const Arg *arg)
{
    toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void tagex(const Arg *arg)
{
    tag(&((Arg) { .ui = 1 << arg->ui }));
}

void toggletagex(const Arg *arg)
{
    toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void tagall(const Arg *arg)
{
    tag(&((Arg) { .ui = ~0 }));
}

/* Signal definitions signum must be greater than 0 */
/* Trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] =
{
    /* signum           function */
    { "focusstack",     focusstack },
    { "setmfact",       setmfact },
    { "togglebar",      togglebar },
    { "incnmaster",     incnmaster },
    { "togglefloating", togglefloating },
    { "focusmon",       focusmon },
    { "tagmon",         tagmon },
    { "zoom",           zoom },
    { "view",           view },
    { "viewall",        viewall },
    { "viewex",         viewex },
    { "toggleview",     view },
    { "toggleviewex",   toggleviewex },
    { "tag",            tag },
    { "tagall",         tagall },
    { "tagex",          tagex },
    { "toggletag",      tag },
    { "toggletagex",    toggletagex },
    { "killclient",     killclient },
    { "quit",           quit },
    { "setlayout",      setlayout },
    { "setlayoutex",    setlayoutex },
};
