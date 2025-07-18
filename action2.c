/* --------------------------------------------------------------------------- */

static const char changedrillsize_syntax[] =
  N_("ChangeDrillSize(Object, delta)\n"
  "ChangeDrillSize(SelectedPins|SelectedVias|Selected|SelectedObjects, delta)");

static const char changedrillsize_help[] =
  N_("Changes the drilling hole size of objects.");

/* %start-doc actions ChangeDrillSize

%end-doc */

static int
ActionChange2ndSize (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  char *delta = ARG (1);
  char *units = ARG (2);
  bool absolute;
  Coord value;

  if (function && delta)
    {
      value = GetValue (delta, units, &absolute);
      switch (GetFunctionID (function))
	{
	case F_Object:
	  {
	    int type;
	    void *ptr1, *ptr2, *ptr3;

	    gui->get_coords (_("Select an Object"), &x, &y);
	    if ((type =
		 SearchScreen (x, y, CHANGE2NDSIZE_TYPES,
			       &ptr1, &ptr2, &ptr3)) != NO_TYPE)
	      if (ChangeObject2ndSize
		  (type, ptr1, ptr2, ptr3, value, absolute, true))
		SetChangedFlag (true);
	    break;
	  }

	case F_SelectedVias:
	  if (ChangeSelected2ndSize (VIA_TYPE, value, absolute))
	    SetChangedFlag (true);
	  break;

	case F_SelectedPins:
	  if (ChangeSelected2ndSize (PIN_TYPE, value, absolute))
	    SetChangedFlag (true);
	  break;
	case F_Selected:
	case F_SelectedObjects:
	  if (ChangeSelected2ndSize (PIN_TYPES, value, absolute))
	    SetChangedFlag (true);
	  break;
	}
    }
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char changeclearsize_syntax[] =
  N_("ChangeClearSize(Object, delta)\n"
  "ChangeClearSize(SelectedPins|SelectedPads|SelectedVias, delta)\n"
  "ChangeClearSize(SelectedLines|SelectedArcs, delta\n"
  "ChangeClearSize(Selected|SelectedObjects, delta)");

static const char changeclearsize_help[] =
  N_("Changes the clearance size of objects.");

/* %start-doc actions ChangeClearSize

If the solder mask is currently showing, this action changes the
solder mask clearance.  If the mask is not showing, this action
changes the polygon clearance.

%end-doc */

static int
ActionChangeClearSize (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  char *delta = ARG (1);
  char *units = ARG (2);
  bool absolute;
  Coord value;

  if (function && delta)
    {
      value = 2 * GetValue (delta, units, &absolute);
      if ((value == 0) && !absolute)
        value = delta[0] == '-' ? -Settings.increments->clear
                                :  Settings.increments->clear;
      switch (GetFunctionID (function))
	{
	case F_Object:
	  {
	    int type;
	    void *ptr1, *ptr2, *ptr3;

	    gui->get_coords (_("Select an Object"), &x, &y);
	    if ((type =
		 SearchScreen (x, y,
			       CHANGECLEARSIZE_TYPES, &ptr1, &ptr2,
			       &ptr3)) != NO_TYPE)
	      if (ChangeObjectClearSize (type, ptr1, ptr2, ptr3, value, absolute))
		SetChangedFlag (true);
	    break;
	  }
	case F_SelectedVias:
	  if (ChangeSelectedClearSize (VIA_TYPE, value, absolute))
	    SetChangedFlag (true);
	  break;
	case F_SelectedPads:
	  if (ChangeSelectedClearSize (PAD_TYPE, value, absolute))
	    SetChangedFlag (true);
	  break;
	case F_SelectedPins:
	  if (ChangeSelectedClearSize (PIN_TYPE, value, absolute))
	    SetChangedFlag (true);
	  break;
	case F_SelectedLines:
	  if (ChangeSelectedClearSize (LINE_TYPE, value, absolute))
	    SetChangedFlag (true);
	  break;
	case F_SelectedArcs:
	  if (ChangeSelectedClearSize (ARC_TYPE, value, absolute))
	    SetChangedFlag (true);
	  break;
	case F_Selected:
	case F_SelectedObjects:
	  if (ChangeSelectedClearSize (CHANGECLEARSIZE_TYPES, value, absolute))
	    SetChangedFlag (true);
	  break;
	}
    }
  return 0;
}

/* ---------------------------------------------------------------------------  */

static const char minmaskgap_syntax[] =
  N_("MinMaskGap(delta)\n"
  "MinMaskGap(Selected, delta)");

static const char minmaskgap_help[] =
  N_("Ensures the mask is a minimum distance from pins and pads.");

/* %start-doc actions MinMaskGap

Checks all specified pins and/or pads, and increases the mask if
needed to ensure a minimum distance between the pin or pad edge and
the mask edge.

%end-doc */

static int
ActionMinMaskGap (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  char *delta = ARG (1);
  char *units = ARG (2);
  bool absolute;
  Coord value;
  Coord thickness;
  int flags;

  if (!function)
    return 1;
  if (strcasecmp (function, "Selected") == 0)
    flags = SELECTEDFLAG;
  else
    {
      units = delta;
      delta = function;
      flags = 0;
    }
  value = 2 * GetValue (delta, units, &absolute);

  SaveUndoSerialNumber ();
  ELEMENT_LOOP (PCB->Data);
  {
    PIN_LOOP (element);
    {
      if (!TEST_FLAGS (flags, pin) || ! pin->Mask) continue;

      thickness = pin->DrillingHole;
      
      if (pin->Thickness > thickness) thickness = pin->Thickness;

      thickness += value;

      if (pin->Mask < thickness)
	{
	  ChangeObjectMaskSize (PIN_TYPE, element, pin, 0, thickness, 1);
	  RestoreUndoSerialNumber ();
	}
    }
    END_LOOP;
    PAD_LOOP (element);
    {
      if (!TEST_FLAGS (flags, pad) || ! pad->Mask)
	continue;
      if (pad->Mask < pad->Thickness + value)
	{
	  ChangeObjectMaskSize (PAD_TYPE, element, pad, 0,
				pad->Thickness + value, 1);
	  RestoreUndoSerialNumber ();
	}
    }
    END_LOOP;
  }
  END_LOOP;
  VIA_LOOP (PCB->Data);
  {
    if (!TEST_FLAGS (flags, via) || ! via->Mask)
      continue;

    thickness = via->DrillingHole;
    if (via->Thickness > thickness)
      thickness = via->Thickness;
    thickness += value;

    if (via->Mask < thickness)
      {
	ChangeObjectMaskSize (VIA_TYPE, via, 0, 0, thickness, 1);
	RestoreUndoSerialNumber ();
      }
  }
  END_LOOP;
  RestoreUndoSerialNumber ();
  IncrementUndoSerialNumber ();
  return 0;
}

/* ---------------------------------------------------------------------------  */

static const char mincleargap_syntax[] =
  N_("MinClearGap(delta)\n"
  "MinClearGap(Selected, delta)");

static const char mincleargap_help[] =
  N_("Ensures that polygons are a minimum distance from objects.");

/* %start-doc actions MinClearGap

Checks all specified objects, and increases the polygon clearance if
needed to ensure a minimum distance between their edges and the
polygon edges.

%end-doc */

static int
ActionMinClearGap (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  char *delta = ARG (1);
  char *units = ARG (2);
  bool absolute;
  Coord value;
  int flags;

  if (!function)
    return 1;
  if (strcasecmp (function, "Selected") == 0)
    flags = SELECTEDFLAG;
  else
    {
      units = delta;
      delta = function;
      flags = 0;
    }
  value = 2 * GetValue (delta, units, &absolute);

  SaveUndoSerialNumber ();
  ELEMENT_LOOP (PCB->Data);
  {
    PIN_LOOP (element);
    {
      if (!TEST_FLAGS (flags, pin))
	continue;
      if (pin->Clearance < value)
	{
	  ChangeObjectClearSize (PIN_TYPE, element, pin, 0,
				value, 1);
	  RestoreUndoSerialNumber ();
	}
    }
    END_LOOP;
    PAD_LOOP (element);
    {
      if (!TEST_FLAGS (flags, pad))
	continue;
      if (pad->Clearance < value)
	{
	  ChangeObjectClearSize (PAD_TYPE, element, pad, 0,
				value, 1);
	  RestoreUndoSerialNumber ();
	}
    }
    END_LOOP;
  }
  END_LOOP;
  VIA_LOOP (PCB->Data);
  {
    if (!TEST_FLAGS (flags, via))
      continue;
    if (via->Clearance < value)
      {
	ChangeObjectClearSize (VIA_TYPE, via, 0, 0, value, 1);
	RestoreUndoSerialNumber ();
      }
  }
  END_LOOP;
  ALLLINE_LOOP (PCB->Data);
  {
    if (!TEST_FLAGS (flags, line))
      continue;
    if (line->Clearance < value)
      {
	ChangeObjectClearSize (LINE_TYPE, layer, line, 0, value, 1);
	RestoreUndoSerialNumber ();
      }
  }
  ENDALL_LOOP;
  ALLARC_LOOP (PCB->Data);
  {
    if (!TEST_FLAGS (flags, arc))
      continue;
    if (arc->Clearance < value)
      {
	ChangeObjectClearSize (ARC_TYPE, layer, arc, 0, value, 1);
	RestoreUndoSerialNumber ();
      }
  }
  ENDALL_LOOP;
  RestoreUndoSerialNumber ();
  IncrementUndoSerialNumber ();
  return 0;
}

/* ---------------------------------------------------------------------------  */

static const char changepinname_syntax[] =
  N_("ChangePinName(ElementName,PinNumber,PinName)");

static const char changepinname_help[] =
  N_("Sets the name of a specific pin on a specific element.");

/* %start-doc actions ChangePinName

This can be especially useful for annotating pin names from a
schematic to the layout without requiring knowledge of the pcb file
format.

@example
ChangePinName(U3, 7, VCC)
@end example

%end-doc */

static int
ActionChangePinName (int argc, char **argv, Coord x, Coord y)
{
  int changed = 0;
  char *refdes, *pinnum, *pinname;

  if (argc != 3)
    {
      AFAIL (changepinname);
    }

  refdes = argv[0];
  pinnum = argv[1];
  pinname = argv[2];

  ELEMENT_LOOP (PCB->Data);
  {
    if (NSTRCMP (refdes, NAMEONPCB_NAME (element)) == 0)
      {
	PIN_LOOP (element);
	{
	  if (NSTRCMP (pinnum, pin->Number) == 0)
	    {
	      AddObjectToChangeNameUndoList (PIN_TYPE, NULL, NULL,
					     pin, pin->Name);
	      /*
	       * Note:  we can't free() pin->Name first because 
	       * it is used in the undo list
	       */
	      pin->Name = strdup (pinname);
	      SetChangedFlag (true);
	      changed = 1;
	    }
	}
	END_LOOP;

	PAD_LOOP (element);
	{
	  if (NSTRCMP (pinnum, pad->Number) == 0)
	    {
	      AddObjectToChangeNameUndoList (PAD_TYPE, NULL, NULL,
					     pad, pad->Name);
	      /* 
	       * Note:  we can't free() pad->Name first because 
	       * it is used in the undo list
	       */
	      pad->Name = strdup (pinname);
	      SetChangedFlag (true);
	      changed = 1;
	    }
	}
	END_LOOP;
      }
  }
  END_LOOP;
  /* 
   * done with our action so increment the undo # if we actually
   * changed anything
   */
  if (changed)
    {
      if (defer_updates)
	defer_needs_update = 1;
      else
	{
	  IncrementUndoSerialNumber ();
	  gui->invalidate_all ();
	}
    }

  return 0;
}

/* --------------------------------------------------------------------------- */

static const char changename_syntax[] =
  N_("ChangeName(Object)\n"
  "ChangeName(Layout|Layer)");

static const char changename_help[] = N_("Sets the name of objects.");

/* %start-doc actions ChangeName

@table @code

@item Object
Changes the name of the element under the cursor.

@item Layout
Changes the name of the layout.  This is printed on the fab drawings.

@item Layer
Changes the name of the currently active layer.

@end table

%end-doc */

int
ActionChangeName (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  char *name;

  if (function)
    {
      switch (GetFunctionID (function))
	{
	  /* change the name of an object */
	case F_Object:
	  {
	    int type;
	    void *ptr1, *ptr2, *ptr3;

	    gui->get_coords (_("Select an Object"), &x, &y);
	    if ((type =
		 SearchScreen (x, y, CHANGENAME_TYPES,
			       &ptr1, &ptr2, &ptr3)) != NO_TYPE)
	      {
		SaveUndoSerialNumber ();
		if (QueryInputAndChangeObjectName (type, ptr1, ptr2, ptr3))
		  {
		    SetChangedFlag (true);
		    if (type == ELEMENT_TYPE)
		      {
			RubberbandType *ptr;
			int i;

			RestoreUndoSerialNumber ();
			Crosshair.AttachedObject.RubberbandN = 0;
			LookupRatLines (type, ptr1, ptr2, ptr3);
			ptr = Crosshair.AttachedObject.Rubberband;
			for (i = 0; i < Crosshair.AttachedObject.RubberbandN;
			     i++, ptr++)
			  {
			    if (PCB->RatOn)
			      EraseRat ((RatType *) ptr->Line);
			    MoveObjectToRemoveUndoList (RATLINE_TYPE,
							ptr->Line, ptr->Line,
							ptr->Line);
			  }
			IncrementUndoSerialNumber ();
			Draw ();
		      }
		  }
	      }
	    break;
	  }

	  /* change the layout's name */
	case F_Layout:
	  name =
	    gui->prompt_for (_("Enter the layout name:"), EMPTY (PCB->Name));
	  /* NB: ChangeLayoutName takes ownership of the passed memory */
	  if (name && ChangeLayoutName (name))
	    SetChangedFlag (true);
	  break;

	  /* change the name of the active layer */
	case F_Layer:
	  name = gui->prompt_for (_("Enter the layer name:"),
				  EMPTY (CURRENT->Name));
	  /* NB: ChangeLayerName takes ownership of the passed memory */
	  if (name && ChangeLayerName (CURRENT, name))
	    SetChangedFlag (true);
	  break;
	}
    }
  return 0;
}


/* --------------------------------------------------------------------------- */

static const char morphpolygon_syntax[] = N_("MorphPolygon(Object|Selected)");

static const char morphpolygon_help[] =
  N_("Converts dead polygon islands into separate polygons.");

/* %start-doc actions MorphPolygon 

If a polygon is divided into unconnected "islands", you can use
this command to convert the otherwise disappeared islands into
separate polygons. Be sure the cursor is over a portion of the
polygon that remains visible. Very small islands that may flake
off are automatically deleted.

%end-doc */

static int
ActionMorphPolygon (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  if (function)
    {
      switch (GetFunctionID (function))
	{
	case F_Object:
	  {
	    int type;
	    void *ptr1, *ptr2, *ptr3;

	    gui->get_coords (_("Select an Object"), &x, &y);
	    if ((type = SearchScreen (x, y, POLYGON_TYPE,
				      &ptr1, &ptr2, &ptr3)) != NO_TYPE)
	      {
		MorphPolygon ((LayerType *) ptr1, (PolygonType *) ptr3);
		Draw ();
		IncrementUndoSerialNumber ();
	      }
	    break;
	  }
	case F_Selected:
	case F_SelectedObjects:
	  ALLPOLYGON_LOOP (PCB->Data);
	  {
	    if (TEST_FLAG (SELECTEDFLAG, polygon))
	      MorphPolygon (layer, polygon);
	  }
	  ENDALL_LOOP;
	  Draw ();
	  IncrementUndoSerialNumber ();
	  break;
	}
    }
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char togglehidename_syntax[] =
  N_("ToggleHideName(Object|SelectedElements)");

static const char togglehidename_help[] =
  N_("Toggles the visibility of element names.");

/* %start-doc actions ToggleHideName

If names are hidden you won't see them on the screen and they will not
appear on the silk layer when you print the layout.

%end-doc */

static int
ActionToggleHideName (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  if (function && PCB->ElementOn)
    {
      switch (GetFunctionID (function))
	{
	case F_Object:
	  {
	    int type;
	    void *ptr1, *ptr2, *ptr3;

	    gui->get_coords (_("Select an Object"), &x, &y);
	    if ((type = SearchScreen (x, y, ELEMENT_TYPE,
				      &ptr1, &ptr2, &ptr3)) != NO_TYPE)
	      {
		AddObjectToFlagUndoList (type, ptr1, ptr2, ptr3);
		EraseElementName ((ElementType *) ptr2);
		TOGGLE_FLAG (HIDENAMEFLAG, (ElementType *) ptr2);
		DrawElementName ((ElementType *) ptr2);
		Draw ();
		IncrementUndoSerialNumber ();
	      }
	    break;
	  }
	case F_SelectedElements:
	case F_Selected:
	  {
	    bool changed = false;
	    ELEMENT_LOOP (PCB->Data);
	    {
	      if ((TEST_FLAG (SELECTEDFLAG, element) ||
		   TEST_FLAG (SELECTEDFLAG,
			      &NAMEONPCB_TEXT (element)))
		  && (FRONT (element) || PCB->InvisibleObjectsOn))
		{
		  AddObjectToFlagUndoList (ELEMENT_TYPE, element,
					   element, element);
		  EraseElementName (element);
		  TOGGLE_FLAG (HIDENAMEFLAG, element);
		  DrawElementName (element);
		  changed = true;
		}
	    }
	    END_LOOP;
	    if (changed)
	      {
		Draw ();
		IncrementUndoSerialNumber ();
	      }
	  }
	}
    }
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char changejoin_syntax[] =
  N_("ChangeJoin(ToggleObject|SelectedLines|SelectedArcs|Selected)");

static const char changejoin_help[] =
  N_("Changes the join (clearance through polygons) of objects.");

/* %start-doc actions ChangeJoin

The join flag determines whether a line or arc, drawn to intersect a
polygon, electrically connects to the polygon or not.  When joined,
the line/arc is simply drawn over the polygon, making an electrical
connection.  When not joined, a gap is drawn between the line and the
polygon, insulating them from each other.

%end-doc */

static int
ActionChangeJoin (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  if (function)
    {
      switch (GetFunctionID (function))
	{
	case F_ToggleObject:
	case F_Object:
	  {
	    int type;
	    void *ptr1, *ptr2, *ptr3;

	    gui->get_coords (_("Select an Object"), &x, &y);
	    if ((type =
		 SearchScreen (x, y, CHANGEJOIN_TYPES,
			       &ptr1, &ptr2, &ptr3)) != NO_TYPE)
	      if (ChangeObjectJoin (type, ptr1, ptr2, ptr3))
		SetChangedFlag (true);
	    break;
	  }

	case F_SelectedLines:
	  if (ChangeSelectedJoin (LINE_TYPE))
	    SetChangedFlag (true);
	  break;

	case F_SelectedArcs:
	  if (ChangeSelectedJoin (ARC_TYPE))
	    SetChangedFlag (true);
	  break;

	case F_Selected:
	case F_SelectedObjects:
	  if (ChangeSelectedJoin (CHANGEJOIN_TYPES))
	    SetChangedFlag (true);
	  break;
	}
    }
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char changesquare_syntax[] =
  N_("ChangeSquare(ToggleObject)\n"
  "ChangeSquare(SelectedElements|SelectedPins)\n"
  "ChangeSquare(Selected|SelectedObjects)");

static const char changesquare_help[] =
  N_("Changes the square flag of pins and pads.");

/* %start-doc actions ChangeSquare

Note that @code{Pins} means both pins and pads.

@pinshapes

%end-doc */

static int
ActionChangeSquare (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  if (function)
    {
      switch (GetFunctionID (function))
	{
	case F_ToggleObject:
	case F_Object:
	  {
	    int type;
	    void *ptr1, *ptr2, *ptr3;

	    gui->get_coords (_("Select an Object"), &x, &y);
	    if ((type =
		 SearchScreen (x, y, CHANGESQUARE_TYPES,
			       &ptr1, &ptr2, &ptr3)) != NO_TYPE)
	      if (ChangeObjectSquare (type, ptr1, ptr2, ptr3))
		SetChangedFlag (true);
	    break;
	  }

	case F_SelectedElements:
	  if (ChangeSelectedSquare (ELEMENT_TYPE))
	    SetChangedFlag (true);
	  break;

	case F_SelectedPins:
	  if (ChangeSelectedSquare (PIN_TYPE | PAD_TYPE))
	    SetChangedFlag (true);
	  break;

	case F_Selected:
	case F_SelectedObjects:
	  if (ChangeSelectedSquare (PIN_TYPE | PAD_TYPE))
	    SetChangedFlag (true);
	  break;
	}
    }
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char setsquare_syntax[] =
  N_("SetSquare(ToggleObject|SelectedElements|SelectedPins)");

static const char setsquare_help[] = N_("sets the square-flag of objects.");

/* %start-doc actions SetSquare

Note that @code{Pins} means pins and pads.

@pinshapes

%end-doc */

static int
ActionSetSquare (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  if (function && *function)
    {
      switch (GetFunctionID (function))
	{
	case F_ToggleObject:
	case F_Object:
	  {
	    int type;
	    void *ptr1, *ptr2, *ptr3;

	    gui->get_coords (_("Select an Object"), &x, &y);
	    if ((type =
		 SearchScreen (x, y, CHANGESQUARE_TYPES,
			       &ptr1, &ptr2, &ptr3)) != NO_TYPE)
	      if (SetObjectSquare (type, ptr1, ptr2, ptr3))
		SetChangedFlag (true);
	    break;
	  }

	case F_SelectedElements:
	  if (SetSelectedSquare (ELEMENT_TYPE))
	    SetChangedFlag (true);
	  break;

	case F_SelectedPins:
	  if (SetSelectedSquare (PIN_TYPE | PAD_TYPE))
	    SetChangedFlag (true);
	  break;

	case F_Selected:
	case F_SelectedObjects:
	  if (SetSelectedSquare (PIN_TYPE | PAD_TYPE))
	    SetChangedFlag (true);
	  break;
	}
    }
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char clearsquare_syntax[] =
  N_("ClearSquare(ToggleObject|SelectedElements|SelectedPins)");

static const char clearsquare_help[] =
  N_("Clears the square-flag of pins and pads.");

/* %start-doc actions ClearSquare

Note that @code{Pins} means pins and pads.

@pinshapes

%end-doc */

static int
ActionClearSquare (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  if (function && *function)
    {
      switch (GetFunctionID (function))
	{
	case F_ToggleObject:
	case F_Object:
	  {
	    int type;
	    void *ptr1, *ptr2, *ptr3;

	    gui->get_coords (_("Select an Object"), &x, &y);
	    if ((type =
		 SearchScreen (x, y, CHANGESQUARE_TYPES,
			       &ptr1, &ptr2, &ptr3)) != NO_TYPE)
	      if (ClrObjectSquare (type, ptr1, ptr2, ptr3))
		SetChangedFlag (true);
	    break;
	  }

	case F_SelectedElements:
	  if (ClrSelectedSquare (ELEMENT_TYPE))
	    SetChangedFlag (true);
	  break;

	case F_SelectedPins:
	  if (ClrSelectedSquare (PIN_TYPE | PAD_TYPE))
	    SetChangedFlag (true);
	  break;

	case F_Selected:
	case F_SelectedObjects:
	  if (ClrSelectedSquare (PIN_TYPE | PAD_TYPE))
	    SetChangedFlag (true);
	  break;
	}
    }
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char changeoctagon_syntax[] =
  N_("ChangeOctagon(Object|ToggleObject|SelectedObjects|Selected)\n"
  "ChangeOctagon(SelectedElements|SelectedPins|SelectedVias)");

static const char changeoctagon_help[] =
  N_("Changes the octagon-flag of pins and vias.");

/* %start-doc actions ChangeOctagon

@pinshapes

%end-doc */

static int
ActionChangeOctagon (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  if (function)
    {
      switch (GetFunctionID (function))
	{
	case F_ToggleObject:
	case F_Object:
	  {
	    int type;
	    void *ptr1, *ptr2, *ptr3;

	    gui->get_coords (_("Select an Object"), &x, &y);
	    if ((type =
		 SearchScreen (x, y, CHANGEOCTAGON_TYPES,
			       &ptr1, &ptr2, &ptr3)) != NO_TYPE)
	      if (ChangeObjectOctagon (type, ptr1, ptr2, ptr3))
		SetChangedFlag (true);
	    break;
	  }

	case F_SelectedElements:
	  if (ChangeSelectedOctagon (ELEMENT_TYPE))
	    SetChangedFlag (true);
	  break;

	case F_SelectedPins:
	  if (ChangeSelectedOctagon (PIN_TYPE))
	    SetChangedFlag (true);
	  break;

	case F_SelectedVias:
	  if (ChangeSelectedOctagon (VIA_TYPE))
	    SetChangedFlag (true);
	  break;

	case F_Selected:
	case F_SelectedObjects:
	  if (ChangeSelectedOctagon (PIN_TYPES))
	    SetChangedFlag (true);
	  break;
	}
    }
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char setoctagon_syntax[] =
  N_("SetOctagon(Object|ToggleObject|SelectedElements|Selected)");

static const char setoctagon_help[] = N_("Sets the octagon-flag of objects.");

/* %start-doc actions SetOctagon

@pinshapes

%end-doc */

static int
ActionSetOctagon (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  if (function)
    {
      switch (GetFunctionID (function))
	{
	case F_ToggleObject:
	case F_Object:
	  {
	    int type;
	    void *ptr1, *ptr2, *ptr3;

	    gui->get_coords (_("Select an Object"), &x, &y);
	    if ((type =
		 SearchScreen (x, y, CHANGEOCTAGON_TYPES,
			       &ptr1, &ptr2, &ptr3)) != NO_TYPE)
	      if (SetObjectOctagon (type, ptr1, ptr2, ptr3))
		SetChangedFlag (true);
	    break;
	  }

	case F_SelectedElements:
	  if (SetSelectedOctagon (ELEMENT_TYPE))
	    SetChangedFlag (true);
	  break;

	case F_SelectedPins:
	  if (SetSelectedOctagon (PIN_TYPE))
	    SetChangedFlag (true);
	  break;

	case F_SelectedVias:
	  if (SetSelectedOctagon (VIA_TYPE))
	    SetChangedFlag (true);
	  break;

	case F_Selected:
	case F_SelectedObjects:
	  if (SetSelectedOctagon (PIN_TYPES))
	    SetChangedFlag (true);
	  break;
	}
    }
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char clearoctagon_syntax[] =
  N_("ClearOctagon(ToggleObject|Object|SelectedObjects|Selected)\n"
  "ClearOctagon(SelectedElements|SelectedPins|SelectedVias)");

static const char clearoctagon_help[] =
  N_("Clears the octagon-flag of pins and vias.");

/* %start-doc actions ClearOctagon

@pinshapes

%end-doc */

static int
ActionClearOctagon (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  if (function)
    {
      switch (GetFunctionID (function))
	{
	case F_ToggleObject:
	case F_Object:
	  {
	    int type;
	    void *ptr1, *ptr2, *ptr3;

	    gui->get_coords (_("Select an Object"), &x, &y);
	    if ((type =
		 SearchScreen (Crosshair.X, Crosshair.Y, CHANGEOCTAGON_TYPES,
			       &ptr1, &ptr2, &ptr3)) != NO_TYPE)
	      if (ClrObjectOctagon (type, ptr1, ptr2, ptr3))
		SetChangedFlag (true);
	    break;
	  }

	case F_SelectedElements:
	  if (ClrSelectedOctagon (ELEMENT_TYPE))
	    SetChangedFlag (true);
	  break;

	case F_SelectedPins:
	  if (ClrSelectedOctagon (PIN_TYPE))
	    SetChangedFlag (true);
	  break;

	case F_SelectedVias:
	  if (ClrSelectedOctagon (VIA_TYPE))
	    SetChangedFlag (true);
	  break;

	case F_Selected:
	case F_SelectedObjects:
	  if (ClrSelectedOctagon (PIN_TYPES))
	    SetChangedFlag (true);
	  break;
	}
    }
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char changehold_syntax[] =
  N_("ChangeHole(ToggleObject|Object|SelectedVias|Selected)");

static const char changehold_help[] = N_("Changes the hole flag of objects.");

/* %start-doc actions ChangeHole

The "hole flag" of a via determines whether the via is a
plated-through hole (not set), or an unplated hole (set).

%end-doc */

static int
ActionChangeHole (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  if (function)
    {
      switch (GetFunctionID (function))
	{
	case F_ToggleObject:
	case F_Object:
	  {
	    int type;
	    void *ptr1, *ptr2, *ptr3;

	    gui->get_coords (_("Select an Object"), &x, &y);
	    if ((type = SearchScreen (x, y, VIA_TYPE,
				      &ptr1, &ptr2, &ptr3)) != NO_TYPE
		&& ChangeHole ((PinType *) ptr3))
	      IncrementUndoSerialNumber ();
	    break;
	  }

	case F_SelectedVias:
	case F_Selected:
	  if (ChangeSelectedHole ())
	    SetChangedFlag (true);
	  break;
	}
    }
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char changepaste_syntax[] =
  N_("ChangePaste(ToggleObject|Object|SelectedPads|Selected)");

static const char changepaste_help[] =
  N_("Changes the no paste flag of objects.");

/* %start-doc actions ChangePaste

The "no paste flag" of a pad determines whether the solderpaste
 stencil will have an opening for the pad (no set) or if there wil be
 no solderpaste on the pad (set).  This is used for things such as
 fiducial pads.

%end-doc */

static int
ActionChangePaste (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  if (function)
    {
      switch (GetFunctionID (function))
	{
	case F_ToggleObject:
	case F_Object:
	  {
	    int type;
	    void *ptr1, *ptr2, *ptr3;

	    gui->get_coords (_("Select an Object"), &x, &y);
	    if ((type = SearchScreen (x, y, PAD_TYPE,
				      &ptr1, &ptr2, &ptr3)) != NO_TYPE
		&& ChangePaste ((PadType *) ptr3))
	      IncrementUndoSerialNumber ();
	    break;
	  }

	case F_SelectedPads:
	case F_Selected:
	  if (ChangeSelectedPaste ())
	    SetChangedFlag (true);
	  break;
	}
    }
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char select_syntax[] =
  N_("Select(Object|ToggleObject)\n"
  "Select(All|Block|Connection|BuriedVias)\n"
  "Select(ElementByName|ObjectByName|PadByName|PinByName)\n"
  "Select(ElementByName|ObjectByName|PadByName|PinByName, Name)\n"
  "Select(TextByName|ViaByName|NetByName)\n"
  "Select(TextByName|ViaByName|NetByName, Name)\n"
  "Select(Convert)");

static const char select_help[] = N_("Toggles or sets the selection.");

/* %start-doc actions Select

@table @code

@item ElementByName
@item ObjectByName
@item PadByName
@item PinByName
@item TextByName
@item ViaByName
@item NetByName

These all rely on having a regular expression parser built into
@code{pcb}.  If the name is not specified then the user is prompted
for a pattern, and all objects that match the pattern and are of the
type specified are selected.

@item Object
@item ToggleObject
Selects the object under the cursor.

@item Block
Selects all objects in a rectangle indicated by the cursor.

@item All
Selects all objects on the board.

@item Found
Selects all connections with the ``found'' flag set.

@item Connection
Selects all connections with the ``connected'' flag set.

@item Connection
Selects all blind and buried vias.

@item Convert
Converts the selected objects to an element.  This uses the highest
numbered paste buffer.

@end table

%end-doc */

static int
ActionSelect (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  if (function)
    {
      switch (GetFunctionID (function))
	{
#if defined(HAVE_REGCOMP) || defined(HAVE_RE_COMP)
	  int type;
	  /* select objects by their names */
	case F_ElementByName:
	  type = ELEMENT_TYPE;
	  goto commonByName;
	case F_ObjectByName:
	  type = ALL_TYPES;
	  goto commonByName;
	case F_PadByName:
	  type = PAD_TYPE;
	  goto commonByName;
	case F_PinByName:
	  type = PIN_TYPE;
	  goto commonByName;
	case F_TextByName:
	  type = TEXT_TYPE;
	  goto commonByName;
	case F_ViaByName:
	  type = VIA_TYPE;
	  goto commonByName;
	case F_NetByName:
	  type = NET_TYPE;
	  goto commonByName;

	commonByName:
	  {
	    char *pattern = ARG (1);

	    if (pattern
		|| (pattern =
		    gui->prompt_for (_("Enter pattern:"), "")) != NULL)
	      {
		if (SelectObjectByName (type, pattern, true))
		  SetChangedFlag (true);
		if (ARG (1) == NULL)
		  free (pattern);
	      }
	    break;
	  }
#endif /* defined(HAVE_REGCOMP) || defined(HAVE_RE_COMP) */

	  /* select a single object */
	case F_ToggleObject:
	case F_Object:
	  if (SelectObject ())
	    SetChangedFlag (true);
	  break;

	  /* all objects in block */
	case F_Block:
	  {
	    BoxType box;

	    box.X1 = MIN (Crosshair.AttachedBox.Point1.X,
			  Crosshair.AttachedBox.Point2.X);
	    box.Y1 = MIN (Crosshair.AttachedBox.Point1.Y,
			  Crosshair.AttachedBox.Point2.Y);
	    box.X2 = MAX (Crosshair.AttachedBox.Point1.X,
			  Crosshair.AttachedBox.Point2.X);
	    box.Y2 = MAX (Crosshair.AttachedBox.Point1.Y,
			  Crosshair.AttachedBox.Point2.Y);
	    notify_crosshair_change (false);
	    NotifyBlock ();
	    if (Crosshair.AttachedBox.State == STATE_THIRD &&
		SelectBlock (&box, true))
	      {
		SetChangedFlag (true);
		Crosshair.AttachedBox.State = STATE_FIRST;
	      }
	    notify_crosshair_change (true);
	    break;
	  }

	  /* select all visible objects */
	case F_All:
	  {
	    BoxType box;

	    box.X1 = -MAX_COORD;
	    box.Y1 = -MAX_COORD;
	    box.X2 = MAX_COORD;
	    box.Y2 = MAX_COORD;
	    if (SelectBlock (&box, true))
	      SetChangedFlag (true);
	    break;
	  }

	  /* all logical connections */
	case F_Found:
	  if (SelectByFlag (FOUNDFLAG, true))
	    {
              Draw ();
	      IncrementUndoSerialNumber ();
	      SetChangedFlag (true);
	    }
	  break;

	  /* all physical connections */
	case F_Connection:
	  if (SelectByFlag (CONNECTEDFLAG, true))
	    {
              Draw ();
	      IncrementUndoSerialNumber ();
	      SetChangedFlag (true);
	    }
	  break;

	case F_BuriedVias:
	  if (SelectBuriedVias (true))
	    {
	      Draw ();
	      IncrementUndoSerialNumber ();
	      SetChangedFlag (true);
	    }
	  break;

	case F_Convert:
	  {
	    Coord x, y;
	    Note.Buffer = Settings.BufferNumber;
	    SetBufferNumber (MAX_BUFFER - 1);
	    ClearBuffer (PASTEBUFFER);
	    gui->get_coords (_("Select the Element's Mark Location"), &x, &y);
	    x = GridFit (x, PCB->Grid, PCB->GridOffsetX);
	    y = GridFit (y, PCB->Grid, PCB->GridOffsetY);
	    AddSelectedToBuffer (PASTEBUFFER, x, y, true);
	    SaveUndoSerialNumber ();
	    RemoveSelected ();
	    ConvertBufferToElement (PASTEBUFFER);
	    RestoreUndoSerialNumber ();
	    CopyPastebufferToLayout (x, y);
	    SetBufferNumber (Note.Buffer);
	  }
	  break;

	default:
	  AFAIL (select);
	  break;
	}
    }
  return 0;
}

/* FLAG(have_regex,FlagHaveRegex,0) */
int
FlagHaveRegex (int parm)
{
#if defined(HAVE_REGCOMP) || defined(HAVE_RE_COMP)
  return 1;
#else
  return 0;
#endif
}

/* --------------------------------------------------------------------------- */

static const char unselect_syntax[] =
  N_("Unselect(All|Block|Connection)\n"
  "Unselect(ElementByName|ObjectByName|PadByName|PinByName)\n"
  "Unselect(ElementByName|ObjectByName|PadByName|PinByName, Name)\n"
  "Unselect(TextByName|ViaByName)\n"
  "Unselect(TextByName|ViaByName, Name)\n");

static const char unselect_help[] =
  N_("Unselects the object at the pointer location or the specified objects.");

/* %start-doc actions Unselect

@table @code

@item All
Unselect all objects.

@item Block
Unselect all objects in a rectangle given by the cursor.

@item Connection
Unselect all connections with the ``found'' flag set.

@item ElementByName
@item ObjectByName
@item PadByName
@item PinByName
@item TextByName
@item ViaByName

These all rely on having a regular expression parser built into
@code{pcb}.  If the name is not specified then the user is prompted
for a pattern, and all objects that match the pattern and are of the
type specified are unselected.


@end table

%end-doc */

static int
ActionUnselect (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  if (function)
    {
      switch (GetFunctionID (function))
	{
#if defined(HAVE_REGCOMP) || defined(HAVE_RE_COMP)
	  int type;
	  /* select objects by their names */
	case F_ElementByName:
	  type = ELEMENT_TYPE;
	  goto commonByName;
	case F_ObjectByName:
	  type = ALL_TYPES;
	  goto commonByName;
	case F_PadByName:
	  type = PAD_TYPE;
	  goto commonByName;
	case F_PinByName:
	  type = PIN_TYPE;
	  goto commonByName;
	case F_TextByName:
	  type = TEXT_TYPE;
	  goto commonByName;
	case F_ViaByName:
	  type = VIA_TYPE;
	  goto commonByName;
	case F_NetByName:
	  type = NET_TYPE;
	  goto commonByName;

	commonByName:
	  {
	    char *pattern = ARG (1);

	    if (pattern
		|| (pattern =
		    gui->prompt_for (_("Enter pattern:"), "")) != NULL)
	      {
		if (SelectObjectByName (type, pattern, false))
		  SetChangedFlag (true);
		if (ARG (1) == NULL)
		  free (pattern);
	      }
	    break;
	  }
#endif /* defined(HAVE_REGCOMP) || defined(HAVE_RE_COMP) */

	  /* all objects in block */
	case F_Block:
	  {
	    BoxType box;

	    box.X1 = MIN (Crosshair.AttachedBox.Point1.X,
			  Crosshair.AttachedBox.Point2.X);
	    box.Y1 = MIN (Crosshair.AttachedBox.Point1.Y,
			  Crosshair.AttachedBox.Point2.Y);
	    box.X2 = MAX (Crosshair.AttachedBox.Point1.X,
			  Crosshair.AttachedBox.Point2.X);
	    box.Y2 = MAX (Crosshair.AttachedBox.Point1.Y,
			  Crosshair.AttachedBox.Point2.Y);
	    notify_crosshair_change (false);
	    NotifyBlock ();
	    if (Crosshair.AttachedBox.State == STATE_THIRD &&
		SelectBlock (&box, false))
	      {
		SetChangedFlag (true);
		Crosshair.AttachedBox.State = STATE_FIRST;
	      }
	    notify_crosshair_change (true);
	    break;
	  }

	  /* unselect all visible objects */
	case F_All:
	  {
	    BoxType box;

	    box.X1 = -MAX_COORD;
	    box.Y1 = -MAX_COORD;
	    box.X2 = MAX_COORD;
	    box.Y2 = MAX_COORD;
	    if (SelectBlock (&box, false))
	      SetChangedFlag (true);
	    break;
	  }

	  /* all logical connections */
	case F_Found:
	  if (SelectByFlag (FOUNDFLAG, false))
	    {
              Draw ();
	      IncrementUndoSerialNumber ();
	      SetChangedFlag (true);
	    }
	  break;

	  /* all physical connections */
	case F_Connection:
	  if (SelectByFlag (CONNECTEDFLAG, false))
	    {
              Draw ();
	      IncrementUndoSerialNumber ();
	      SetChangedFlag (true);
	    }
	  break;

	default:
	  AFAIL (unselect);
	  break;

	}
    }
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char saveto_syntax[] =
  N_("SaveTo(Layout|LayoutAs,filename)\n"
  "SaveTo(AllConnections|AllUnusedPins|ElementConnections,filename)\n"
  "SaveTo(PasteBuffer,filename)");

static const char saveto_help[] = N_("Saves data to a file.");

/* %start-doc actions SaveTo

@table @code

@item Layout
Saves the current layout.

@item LayoutAs
Saves the current layout, and remembers the filename used.

@item AllConnections
Save all connections to a file.

@item AllUnusedPins
List all unused pins to a file.

@item ElementConnections
Save connections to the element at the cursor to a file.

@item PasteBuffer
Save the content of the active Buffer to a file. This is the graphical way to create a footprint.

@end table

%end-doc */

static int
ActionSaveTo (int argc, char **argv, Coord x, Coord y)
{
  char *function;
  char *name;

  function = ARG (0);
  
  if ( ! function || strcasecmp (function, "Layout") == 0)
    {
      if (SavePCB (PCB->Filename) == 0)
        SetChangedFlag (false);
      return 0;
    }

  if (argc != 2)
    AFAIL (saveto);

  name = argv[1];

  if (strcasecmp (function, "LayoutAs") == 0)
    {
      if (SavePCB (name) == 0)
        {
          SetChangedFlag (false);
          free (PCB->Filename);
          PCB->Filename = strdup (name);
          if (gui->notify_filename_changed != NULL)
            gui->notify_filename_changed ();
        }
      return 0;
    }

  if (strcasecmp (function, "AllConnections") == 0)
    {
      FILE *fp;
      bool result;
      if ((fp = CheckAndOpenFile (name, true, false, &result, NULL)) != NULL)
	{
	  LookupConnectionsToAllElements (fp);
	  fclose (fp);
	  SetChangedFlag (true);
	}
      return 0;
    }

  if (strcasecmp (function, "AllUnusedPins") == 0)
    {
      FILE *fp;
      bool result;
      if ((fp = CheckAndOpenFile (name, true, false, &result, NULL)) != NULL)
	{
	  LookupUnusedPins (fp);
	  fclose (fp);
	  SetChangedFlag (true);
	}
      return 0;
    }

  if (strcasecmp (function, "ElementConnections") == 0)
    {
      ElementType *element;
      void *ptrtmp;
      FILE *fp;
      bool result;

      if ((SearchScreen (Crosshair.X, Crosshair.Y, ELEMENT_TYPE,
			 &ptrtmp, &ptrtmp, &ptrtmp)) != NO_TYPE)
	{
	  element = (ElementType *) ptrtmp;
	  if ((fp =
	       CheckAndOpenFile (name, true, false, &result, NULL)) != NULL)
	    {
	      LookupElementConnections (element, fp);
	      fclose (fp);
	      SetChangedFlag (true);
	    }
	}
      return 0;
    }

  if (strcasecmp (function, "PasteBuffer") == 0)
    {
      return SaveBufferElements (name);
    }

  AFAIL (saveto);
}

/* --------------------------------------------------------------------------- */

static const char savesettings_syntax[] =
  N_("SaveSettings()\n"
  "SaveSettings(local)");

static const char savesettings_help[] = N_("Saves settings.");

/* %start-doc actions SaveSettings

If you pass no arguments, the settings are stored in
@code{$HOME/.pcb/settings}.  If you pass the word @code{local} they're
saved in @code{./pcb.settings}.

%end-doc */

static int
ActionSaveSettings (int argc, char **argv, Coord x, Coord y)
{
  int locally = argc > 0 ? (strncasecmp (argv[0], "local", 5) == 0) : 0;
  hid_save_settings (locally);
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char loadfrom_syntax[] =
  N_("LoadFrom(Layout|LayoutToBuffer|ElementToBuffer|Netlist|Revert,filename)");

static const char loadfrom_help[] = N_("Load layout data from a file.");

/* %start-doc actions LoadFrom

This action assumes you know what the filename is.  The various GUIs
should have a similar @code{Load} action where the filename is
optional, and will provide their own file selection mechanism to let
you choose the file name.

@table @code

@item Layout
Loads an entire PCB layout, replacing the current one.

@item LayoutToBuffer
Loads an entire PCB layout to the paste buffer.

@item ElementToBuffer
Loads the given element file into the paste buffer.  Element files
contain only a single @code{Element} definition, such as the
``newlib'' library uses.

@item Netlist
Loads a new netlist, replacing any current netlist.

@item Revert
Re-loads the current layout from its disk file, reverting any changes
you may have made.

@end table

%end-doc */

static int
ActionLoadFrom (int argc, char **argv, Coord x, Coord y)
{
  char *function;
  char *name;

  if (argc < 2)
    AFAIL (loadfrom);

  function = argv[0];
  name = argv[1];

  if (strcasecmp (function, "ElementToBuffer") == 0)
    {
      notify_crosshair_change (false);
      if (LoadElementToBuffer (PASTEBUFFER, name, true))
	SetMode (PASTEBUFFER_MODE);
      notify_crosshair_change (true);
    }

  else if (strcasecmp (function, "LayoutToBuffer") == 0)
    {
      notify_crosshair_change (false);
      if (LoadLayoutToBuffer (PASTEBUFFER, name))
	SetMode (PASTEBUFFER_MODE);
      notify_crosshair_change (true);
    }

  else if (strcasecmp (function, "Layout") == 0)
    {
      if (!PCB->Changed ||
	  gui->confirm_dialog (_("OK to override layout data?"), 0))
	LoadPCB (name);
    }

  else if (strcasecmp (function, "Netlist") == 0)
    {
      if (PCB->Netlistname)
	free (PCB->Netlistname);
      PCB->Netlistname = StripWhiteSpaceAndDup (name);
      FreeLibraryMemory (&PCB->NetlistLib);
      ImportNetlist (PCB->Netlistname);
      NetlistChanged (1);
      netlist_loaded = true;
    }
  else if (strcasecmp (function, "Revert") == 0 && PCB->Filename
	   && (!PCB->Changed
	       || gui->confirm_dialog (_("OK to override changes?"), 0)))
    {
      RevertPCB ();
    }

  return 0;
}

/* --------------------------------------------------------------------------- */

static const char new_syntax[] = N_("New([name])");

static const char new_help[] = N_("Starts a new layout.");

/* %start-doc actions New

If a name is not given, one is prompted for.

%end-doc */

static int
ActionNew (int argc, char **argv, Coord x, Coord y)
{
  char *name = ARG (0);

  if (!PCB->Changed || gui->confirm_dialog (_("OK to clear layout data?"), 0))
    {
      if (name)
	name = strdup (name);
      else
	name = gui->prompt_for (_("Enter the layout name:"), "");

      if (!name)
        return 1;

      notify_crosshair_change (false);
      /* do emergency saving
       * clear the old struct and allocate memory for the new one
       */
      if (PCB->Changed && Settings.SaveInTMP)
	SaveInTMP ();
      RemovePCB (PCB);
      PCB = NULL;
      PCB = CreateNewPCB ();
      CreateNewPCBPost (PCB, 1);

      /* setup the new name and reset some values to default */
      free (PCB->Name);
      PCB->Name = name;

      ResetStackAndVisibility ();
      CenterDisplay (PCB->MaxWidth / 2, PCB->MaxHeight / 2, false);
      Redraw ();

      hid_action ("PCBChanged");
      notify_crosshair_change (true);
      return 0;
    }
  return 1;
}

/*!
 * \brief No operation, just for testing purposes.
 * syntax: Bell(volume)
 */
void
ActionBell (char *volume)
{
  gui->beep ();
}

/* --------------------------------------------------------------------------- */

static const char pastebuffer_syntax[] =
  N_("PasteBuffer(AddSelected|Clear|1..MAX_BUFFER)\n"
  "PasteBuffer(Rotate, 1..3)\n"
  "PasteBuffer(Convert|Save|Restore|Mirror)\n"
  "PasteBuffer(ToLayout, X, Y, units)");

static const char pastebuffer_help[] =
  N_("Various operations on the paste buffer.");

/* %start-doc actions PasteBuffer

There are a number of paste buffers; the actual limit is a
compile-time constant @code{MAX_BUFFER} in @file{globalconst.h}.  It
is currently @code{5}.  One of these is the ``current'' paste buffer,
often referred to as ``the'' paste buffer.

@table @code

@item AddSelected
Copies the selected objects to the current paste buffer.

@item Clear
Remove all objects from the current paste buffer.

@item Convert
Convert the current paste buffer to an element.  Vias are converted to
pins, lines are converted to pads.

@item Restore
Convert any elements in the paste buffer back to vias and lines.

@item Mirror
Flip all objects in the paste buffer vertically (up/down flip).  To mirror
horizontally, combine this with rotations.

@item Rotate
Rotates the current buffer.  The number to pass is 1..3, where 1 means
90 degrees counter clockwise, 2 means 180 degrees, and 3 means 90
degrees clockwise (270 CCW).

@item Save
Saves any elements in the current buffer to the indicated file.

@item ToLayout
Pastes any elements in the current buffer to the indicated X, Y
coordinates in the layout.  The @code{X} and @code{Y} are treated like
@code{delta} is for many other objects.  For each, if it's prefixed by
@code{+} or @code{-}, then that amount is relative to the last
location.  Otherwise, it's absolute.  Units can be
@code{mil} or @code{mm}; if unspecified, units are PCB's internal
units, currently 1/100 mil.


@item 1..MAX_BUFFER
Selects the given buffer to be the current paste buffer.

@end table

%end-doc */

static int
ActionPasteBuffer (int argc, char **argv, Coord x, Coord y)
{
  char *function = argc ? argv[0] : (char *)"";
  char *sbufnum = argc > 1 ? argv[1] : (char *)"";
  char *name;
  static char *default_file = NULL;
  int free_name = 0;

  notify_crosshair_change (false);
  if (function)
    {
      switch (GetFunctionID (function))
	{
	  /* clear contents of paste buffer */
	case F_Clear:
	  ClearBuffer (PASTEBUFFER);
	  break;

	  /* copies objects to paste buffer */
	case F_AddSelected:
	  AddSelectedToBuffer (PASTEBUFFER, 0, 0, false);
	  break;

	  /* converts buffer contents into an element */
	case F_Convert:
	  ConvertBufferToElement (PASTEBUFFER);
	  break;

	  /* break up element for editing */
	case F_Restore:
	  SmashBufferElement (PASTEBUFFER);
	  break;

	  /* Mirror buffer */
	case F_Mirror:
	  MirrorBuffer (PASTEBUFFER);
	  break;

	case F_Rotate:
	  if (sbufnum)
	    {
	      RotateBuffer (PASTEBUFFER, (BYTE) atoi (sbufnum));
        crosshair_update_range();
	    }
	  break;

	case F_Save:
	  if (PASTEBUFFER->Data->ElementN == 0)
	    {
	      Message (_("Buffer has no elements!\n"));
	      break;
	    }
	  free_name = 0;
	  if (argc <= 1)
	    {
	      name = gui->fileselect (_("Save Paste Buffer As ..."),
				      _("Choose a file to save the contents of the\n"
					"paste buffer to.\n"),
				      default_file, ".fp", "footprint",
				      0);

	      if (default_file)
		{
		  free (default_file);
		  default_file = NULL;
		}
	      if ( name && *name)
		{
		  default_file = strdup (name);
		}
	      free_name = 1;
	    }
	      
	  else
	    name = argv[1];

	  {
	    FILE *exist;

	    if ((exist = fopen (name, "r")))
	      {
		fclose (exist);
		if (gui->
		    confirm_dialog (_("File exists!  Ok to overwrite?"), 0))
		  SaveBufferElements (name);
	      }
	    else
	      SaveBufferElements (name);

	    if (free_name && name)
	      free (name);
	  }
	  break;

	case F_ToLayout:
	  {
	    static Coord oldx = 0, oldy = 0;
	    Coord x, y;
	    bool absolute;

	    if (argc == 1)
	      {
		x = y = 0;
	      }
	    else if (argc == 3 || argc == 4)
	      {
		x = GetValue (ARG (1), ARG (3), &absolute);
		if (!absolute)
		  x += oldx;
		y = GetValue (ARG (2), ARG (3), &absolute);
		if (!absolute)
		  y += oldy;
	      }
	    else
	      {
		notify_crosshair_change (true);
		AFAIL (pastebuffer);
	      }

	    oldx = x;
	    oldy = y;
	    if (CopyPastebufferToLayout (x, y))
	      SetChangedFlag (true);
	  }
	  break;

	  /* set number */
	default:
	  {
	    int number = atoi (function);

	    /* correct number */
	    if (number)
	      SetBufferNumber (number - 1);
	  }
	}
    }

  notify_crosshair_change (true);
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char undo_syntax[] = N_("Undo()\n"
                                  "Undo(ClearList)");

static const char undo_help[] = N_("Undo recent changes.");

/* %start-doc actions Undo

The unlimited undo feature of @code{Pcb} allows you to recover from
most operations that materially affect you work.  Calling
@code{Undo()} without any parameter recovers from the last (non-undo)
operation. @code{ClearList} is used to release the allocated
memory. @code{ClearList} is called whenever a new layout is started or
loaded. See also @code{Redo} and @code{Atomic}.

Note that undo groups operations by serial number; changes with the
same serial number will be undone (or redone) as a group.  See
@code{Atomic}.

%end-doc */

static int
ActionUndo (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  if (!function || !*function)
    {
      /* don't allow undo in the middle of an operation */
      if (Settings.Mode != POLYGONHOLE_MODE &&
	  Crosshair.AttachedObject.State != STATE_FIRST)
	return 1;
      if (Crosshair.AttachedBox.State != STATE_FIRST
	  && Settings.Mode != ARC_MODE)
	return 1;
      /* undo the last operation */

      notify_crosshair_change (false);
      if ((Settings.Mode == POLYGON_MODE ||
           Settings.Mode == POLYGONHOLE_MODE) &&
          Crosshair.AttachedPolygon.PointN)
	{
	  GoToPreviousPoint ();
	  notify_crosshair_change (true);
	  return 0;
	}
      /* move anchor point if undoing during line creation */
      if (Settings.Mode == LINE_MODE)
	{
	  if (Crosshair.AttachedLine.State == STATE_SECOND)
	    {
	      if (TEST_FLAG (AUTODRCFLAG, PCB))
		Undo (true);	/* undo the connection find */
	      Crosshair.AttachedLine.State = STATE_FIRST;
	      SetLocalRef (0, 0, false);
	      notify_crosshair_change (true);
	      return 0;
	    }
	  if (Crosshair.AttachedLine.State == STATE_THIRD)
	    {
	      int type;
	      void *ptr1, *ptr3, *ptrtmp;
	      LineType *ptr2;
	      /* this search is guaranteed to succeed */
	      SearchObjectByLocation (LINE_TYPE | RATLINE_TYPE, &ptr1,
				      &ptrtmp, &ptr3,
				      Crosshair.AttachedLine.Point1.X,
				      Crosshair.AttachedLine.Point1.Y, 0);
	      ptr2 = (LineType *) ptrtmp;

	      /* save both ends of line */
	      Crosshair.AttachedLine.Point2.X = ptr2->Point1.X;
	      Crosshair.AttachedLine.Point2.Y = ptr2->Point1.Y;
	      if ((type = Undo (true)))
		SetChangedFlag (true);
	      /* check that the undo was of the right type */
	      if ((type & UNDO_CREATE) == 0)
		{
		  /* wrong undo type, restore anchor points */
		  Crosshair.AttachedLine.Point2.X =
		    Crosshair.AttachedLine.Point1.X;
		  Crosshair.AttachedLine.Point2.Y =
		    Crosshair.AttachedLine.Point1.Y;
		  notify_crosshair_change (true);
		  return 0;
		}
	      /* move to new anchor */
	      Crosshair.AttachedLine.Point1.X =
		Crosshair.AttachedLine.Point2.X;
	      Crosshair.AttachedLine.Point1.Y =
		Crosshair.AttachedLine.Point2.Y;
	      /* check if an intermediate point was removed */
	      if (type & UNDO_REMOVE)
		{
		  /* this search should find the restored line */
		  SearchObjectByLocation (LINE_TYPE | RATLINE_TYPE, &ptr1,
					  &ptrtmp,
					  &ptr3,
					  Crosshair.AttachedLine.Point2.X,
					  Crosshair.AttachedLine.Point2.Y, 0);
		  ptr2 = (LineType *) ptrtmp;
	          if (TEST_FLAG (AUTODRCFLAG, PCB))
		    {
		      /* undo loses CONNECTEDFLAG and FOUNDFLAG */
		      SET_FLAG(CONNECTEDFLAG, ptr2);
		      SET_FLAG(FOUNDFLAG, ptr2);
		      DrawLine (CURRENT, ptr2);
		    }
		  Crosshair.AttachedLine.Point1.X =
		    Crosshair.AttachedLine.Point2.X = ptr2->Point2.X;
		  Crosshair.AttachedLine.Point1.Y =
		    Crosshair.AttachedLine.Point2.Y = ptr2->Point2.Y;
		}
	      FitCrosshairIntoGrid (Crosshair.X, Crosshair.Y);
	      AdjustAttachedObjects ();
	      if (--addedLines == 0)
		{
		  Crosshair.AttachedLine.State = STATE_SECOND;
		  lastLayer = CURRENT;
		}
	      else
		{
		  /* this search is guaranteed to succeed too */
		  SearchObjectByLocation (LINE_TYPE | RATLINE_TYPE, &ptr1,
					  &ptrtmp,
					  &ptr3,
					  Crosshair.AttachedLine.Point1.X,
					  Crosshair.AttachedLine.Point1.Y, 0);
		  ptr2 = (LineType *) ptrtmp;
		  lastLayer = (LayerType *) ptr1;
		}
	      notify_crosshair_change (true);
	      return 0;
	    }
	}
      if (Settings.Mode == ARC_MODE)
	{
	  if (Crosshair.AttachedBox.State == STATE_SECOND)
	    {
	      Crosshair.AttachedBox.State = STATE_FIRST;
	      notify_crosshair_change (true);
	      return 0;
	    }
	  if (Crosshair.AttachedBox.State == STATE_THIRD)
	    {
	      void *ptr1, *ptr2, *ptr3;
	      BoxType *bx;
	      /* guaranteed to succeed */
	      SearchObjectByLocation (ARC_TYPE, &ptr1, &ptr2, &ptr3,
				      Crosshair.AttachedBox.Point1.X,
				      Crosshair.AttachedBox.Point1.Y, 0);
	      bx = GetArcEnds ((ArcType *) ptr2);
	      Crosshair.AttachedBox.Point1.X =
		Crosshair.AttachedBox.Point2.X = bx->X1;
	      Crosshair.AttachedBox.Point1.Y =
		Crosshair.AttachedBox.Point2.Y = bx->Y1;
	      AdjustAttachedObjects ();
	      if (--addedLines == 0)
		Crosshair.AttachedBox.State = STATE_SECOND;
	    }
	}
      /* undo the last destructive operation */
      if (Undo (true))
	SetChangedFlag (true);
    }
  else if (function)
    {
      switch (GetFunctionID (function))
	{
	  /* clear 'undo objects' list */
	case F_ClearList:
	  ClearUndoList (false);
	  break;
	}
    }
  notify_crosshair_change (true);
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char redo_syntax[] = N_("Redo()");

static const char redo_help[] = N_("Redo recent \"undo\" operations.");

/* %start-doc actions Redo

This routine allows you to recover from the last undo command.  You
might want to do this if you thought that undo was going to revert
something other than what it actually did (in case you are confused
about which operations are un-doable), or if you have been backing up
through a long undo list and over-shoot your stopping point.  Any
change that is made since the undo in question will trim the redo
list.  For example if you add ten lines, then undo three of them you
could use redo to put them back, but if you move a line on the board
before performing the redo, you will lose the ability to "redo" the
three "undone" lines.

%end-doc */

static int
ActionRedo (int argc, char **argv, Coord x, Coord y)
{
  if (((Settings.Mode == POLYGON_MODE ||
        Settings.Mode == POLYGONHOLE_MODE) &&
       Crosshair.AttachedPolygon.PointN) ||
      Crosshair.AttachedLine.State == STATE_SECOND)
    return 1;
  notify_crosshair_change (false);
  if (Redo (true))
    {
      SetChangedFlag (true);
      if (Settings.Mode == LINE_MODE &&
	  Crosshair.AttachedLine.State != STATE_FIRST)
	{
	  LineType *line = g_list_last (CURRENT->Line)->data;
	  Crosshair.AttachedLine.Point1.X =
	    Crosshair.AttachedLine.Point2.X = line->Point2.X;
	  Crosshair.AttachedLine.Point1.Y =
	    Crosshair.AttachedLine.Point2.Y = line->Point2.Y;
	  addedLines++;
	}
    }
  notify_crosshair_change (true);
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char polygon_syntax[] = N_("Polygon(Close|PreviousPoint)");

static const char polygon_help[] = N_("Some polygon related stuff.");

/* %start-doc actions Polygon

Polygons need a special action routine to make life easier.

@table @code

@item Close
Creates the final segment of the polygon.  This may fail if clipping
to 45 degree lines is switched on, in which case a warning is issued.

@item PreviousPoint
Resets the newly entered corner to the previous one. The Undo action
will call Polygon(PreviousPoint) when appropriate to do so.

@end table

%end-doc */

static int
ActionPolygon (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  if (function && Settings.Mode == POLYGON_MODE)
    {
      notify_crosshair_change (false);
      switch (GetFunctionID (function))
	{
	  /* close open polygon if possible */
	case F_Close:
	  ClosePolygon ();
	  break;

	  /* go back to the previous point */
	case F_PreviousPoint:
	  GoToPreviousPoint ();
	  break;
	}
      notify_crosshair_change (true);
    }
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char routestyle_syntax[] = N_("RouteStyle(1|2|3|4)");

static const char routestyle_help[] =
  N_("Copies the indicated routing style into the current sizes.");

/* %start-doc actions RouteStyle

%end-doc */

static int
ActionRouteStyle (int argc, char **argv, Coord x, Coord y)
{
  char *str = ARG (0);
  RouteStyleType *rts;
  int number;

  if (str)
    {
      number = atoi (str);
      if (number > 0 && number <= NUM_STYLES)
	{
	  rts = &PCB->RouteStyle[number - 1];
	  SetLineSize (rts->Thick);
	  SetViaSize (rts->Diameter, true);
	  SetViaDrillingHole (rts->Hole, true);
	  SetKeepawayWidth (rts->Keepaway);
    SetViaMaskAperture(rts->ViaMask);
	  hid_action("RouteStylesChanged");
	}
    }
  return 0;
}


/* --------------------------------------------------------------------------- */

static const char moveobject_syntax[] = N_("MoveObject(X,Y,dim)");

static const char moveobject_help[] =
  N_("Moves the object under the crosshair.");

/* %start-doc actions MoveObject

The @code{X} and @code{Y} are treated like @code{delta} is for many
other objects.  For each, if it's prefixed by @code{+} or @code{-},
then that amount is relative.  Otherwise, it's absolute.  Units can be
@code{mil} or @code{mm}; if unspecified, units are PCB's internal
units, currently 1/100 mil.

%end-doc */

static int
ActionMoveObject (int argc, char **argv, Coord x, Coord y)
{
  char *x_str = ARG (0);
  char *y_str = ARG (1);
  char *units = ARG (2);
  Coord nx, ny;
  bool absolute1, absolute2;
  void *ptr1, *ptr2, *ptr3;
  int type;

  ny = GetValue (y_str, units, &absolute1);
  nx = GetValue (x_str, units, &absolute2);

  type = SearchScreen (x, y, MOVE_TYPES, &ptr1, &ptr2, &ptr3);
  if (type == NO_TYPE)
    {
      Message (_("Nothing found under crosshair\n"));
      return 1;
    }
  if (absolute1)
    nx -= x;
  if (absolute2)
    ny -= y;
  Crosshair.AttachedObject.RubberbandN = 0;
  if (TEST_FLAG (RUBBERBANDFLAG, PCB))
    LookupRubberbandLines (type, ptr1, ptr2, ptr3);
  if (type == ELEMENT_TYPE)
    LookupRatLines (type, ptr1, ptr2, ptr3);
  MoveObjectAndRubberband (type, ptr1, ptr2, ptr3, nx, ny);
  SetChangedFlag (true);
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char movetocurrentlayer_syntax[] =
  N_("MoveToCurrentLayer(Object|SelectedObjects)");

static const char movetocurrentlayer_help[] =
  N_("Moves objects to the current layer.");

/* %start-doc actions MoveToCurrentLayer

Note that moving an element from a component layer to a solder layer,
or from solder to component, won't automatically flip it.  Use the
@code{Flip()} action to do that.

%end-doc */

static int
ActionMoveToCurrentLayer (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  if (function)
    {
      switch (GetFunctionID (function))
	{
	case F_Object:
	  {
	    int type;
	    void *ptr1, *ptr2, *ptr3;

	    gui->get_coords (_("Select an Object"), &x, &y);
	    if ((type =
		 SearchScreen (x, y, MOVETOLAYER_TYPES,
			       &ptr1, &ptr2, &ptr3)) != NO_TYPE)
	      if (MoveObjectToLayer (type, ptr1, ptr2, ptr3, CURRENT, false))
		SetChangedFlag (true);
	    break;
	  }

	case F_SelectedObjects:
	case F_Selected:
	  if (MoveSelectedObjectsToLayer (CURRENT))
	    SetChangedFlag (true);
	  break;
	}
    }
  return 0;
}


static const char setsame_syntax[] = N_("SetSame()");

static const char setsame_help[] =
  N_("Sets current layer and sizes to match indicated item.");

/* %start-doc actions SetSame

When invoked over any line, arc, polygon, or via, this changes the
current layer to be the layer that item is on, and changes the current
sizes (thickness, keepaway, drill, etc) according to that item.

%end-doc */

static int
ActionSetSame (int argc, char **argv, Coord x, Coord y)
{
  void *ptr1, *ptr2, *ptr3;
  int type;
  LayerType *layer = CURRENT;

  type = SearchScreen (x, y, CLONE_TYPES, &ptr1, &ptr2, &ptr3);
/* set layer current and size from line or arc */
  switch (type)
    {
    case LINE_TYPE:
      notify_crosshair_change (false);
      Settings.LineThickness = ((LineType *) ptr2)->Thickness;
      Settings.Keepaway = ((LineType *) ptr2)->Clearance / 2;
      layer = (LayerType *) ptr1;
      if (Settings.Mode != LINE_MODE)
	SetMode (LINE_MODE);
      notify_crosshair_change (true);
      hid_action ("RouteStylesChanged");
      break;

    case ARC_TYPE:
      notify_crosshair_change (false);
      Settings.LineThickness = ((ArcType *) ptr2)->Thickness;
      Settings.Keepaway = ((ArcType *) ptr2)->Clearance / 2;
      layer = (LayerType *) ptr1;
      if (Settings.Mode != ARC_MODE)
	SetMode (ARC_MODE);
      notify_crosshair_change (true);
      hid_action ("RouteStylesChanged");
      break;

    case POLYGON_TYPE:
      layer = (LayerType *) ptr1;
      break;

    case VIA_TYPE:
      notify_crosshair_change (false);
      Settings.ViaThickness = ((PinType *) ptr2)->Thickness;
      Settings.ViaDrillingHole = ((PinType *) ptr2)->DrillingHole;
      Settings.Keepaway = ((PinType *) ptr2)->Clearance / 2;
      if (Settings.Mode != VIA_MODE)
	SetMode (VIA_MODE);
      notify_crosshair_change (true);
      hid_action ("RouteStylesChanged");
      break;

    default:
      return 1;
    }
  if (layer != CURRENT)
    {
      ChangeGroupVisibility (GetLayerNumber (PCB->Data, layer), true, true);
      Redraw ();
    }
  return 0;
}


/* --------------------------------------------------------------------------- */

static const char setflag_syntax[] =
  N_("SetFlag(Object|Selected|SelectedObjects, flag)\n"
  "SetFlag(SelectedLines|SelectedPins|SelectedVias, flag)\n"
  "SetFlag(SelectedPads|SelectedTexts|SelectedNames, flag)\n"
  "SetFlag(SelectedElements, flag)\n"
  "flag = square | octagon | thermal | join");

static const char setflag_help[] = N_("Sets flags on objects.");

/* %start-doc actions SetFlag

Turns the given flag on, regardless of its previous setting.  See
@code{ChangeFlag}.

@example
SetFlag(SelectedPins,thermal)
@end example

%end-doc */

static int
ActionSetFlag (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  char *flag = ARG (1);
  ChangeFlag (function, flag, 1, "SetFlag");
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char clrflag_syntax[] =
  N_("ClrFlag(Object|Selected|SelectedObjects, flag)\n"
  "ClrFlag(SelectedLines|SelectedPins|SelectedVias, flag)\n"
  "ClrFlag(SelectedPads|SelectedTexts|SelectedNames, flag)\n"
  "ClrFlag(SelectedElements, flag)\n"
  "flag = square | octagon | thermal | join");

static const char clrflag_help[] = N_("Clears flags on objects.");

/* %start-doc actions ClrFlag

Turns the given flag off, regardless of its previous setting.  See
@code{ChangeFlag}.

@example
ClrFlag(SelectedLines,join)
@end example

%end-doc */

static int
ActionClrFlag (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  char *flag = ARG (1);
  ChangeFlag (function, flag, 0, "ClrFlag");
  return 0;
}

/* --------------------------------------------------------------------------- */

static const char changeflag_syntax[] =
  N_("ChangeFlag(Object|Selected|SelectedObjects, flag, value)\n"
  "ChangeFlag(SelectedLines|SelectedPins|SelectedVias, flag, value)\n"
  "ChangeFlag(SelectedPads|SelectedTexts|SelectedNames, flag, value)\n"
  "ChangeFlag(SelectedElements, flag, value)\n"
  "flag = square | octagon | thermal | join\n"
  "value = 0 | 1");

static const char changeflag_help[] = N_("Sets or clears flags on objects.");

/* %start-doc actions ChangeFlag

Toggles the given flag on the indicated object(s).  The flag may be
one of the flags listed above (square, octagon, thermal, join).  The
value may be the number 0 or 1.  If the value is 0, the flag is
cleared.  If the value is 1, the flag is set.

%end-doc */

static int
ActionChangeFlag (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  char *flag = ARG (1);
  int value = argc > 2 ? atoi (argv[2]) : -1;
  if (value != 0 && value != 1)
    AFAIL (changeflag);

  ChangeFlag (function, flag, value, "ChangeFlag");
  return 0;
}


static void
ChangeFlag (char *what, char *flag_name, int value, char *cmd_name)
{
  bool (*set_object) (int, void *, void *, void *);
  bool (*set_selected) (int);

  if (NSTRCMP (flag_name, "square") == 0)
    {
      set_object = value ? SetObjectSquare : ClrObjectSquare;
      set_selected = value ? SetSelectedSquare : ClrSelectedSquare;
    }
  else if (NSTRCMP (flag_name, "octagon") == 0)
    {
      set_object = value ? SetObjectOctagon : ClrObjectOctagon;
      set_selected = value ? SetSelectedOctagon : ClrSelectedOctagon;
    }
  else if (NSTRCMP (flag_name, "join") == 0)
    {
      /* Note: these are backwards, because the flag is "clear" but
         the command is "join".  */
      set_object = value ? ClrObjectJoin : SetObjectJoin;
      set_selected = value ? ClrSelectedJoin : SetSelectedJoin;
    }
  else
    {
      Message (_("%s():  Flag \"%s\" is not valid\n"), cmd_name, flag_name);
      return;
    }

  switch (GetFunctionID (what))
    {
    case F_Object:
      {
	int type;
	void *ptr1, *ptr2, *ptr3;

	if ((type =
	     SearchScreen (Crosshair.X, Crosshair.Y, CHANGESIZE_TYPES,
			   &ptr1, &ptr2, &ptr3)) != NO_TYPE)
	  if (TEST_FLAG (LOCKFLAG, (PinType *) ptr2))
	    Message (_("Sorry, the object is locked\n"));
	if (set_object (type, ptr1, ptr2, ptr3))
	  SetChangedFlag (true);
	break;
      }

    case F_SelectedVias:
      if (set_selected (VIA_TYPE))
	SetChangedFlag (true);
      break;

    case F_SelectedPins:
      if (set_selected (PIN_TYPE))
	SetChangedFlag (true);
      break;

    case F_SelectedPads:
      if (set_selected (PAD_TYPE))
	SetChangedFlag (true);
      break;

    case F_SelectedLines:
      if (set_selected (LINE_TYPE))
	SetChangedFlag (true);
      break;

    case F_SelectedTexts:
      if (set_selected (TEXT_TYPE))
	SetChangedFlag (true);
      break;

    case F_SelectedNames:
      if (set_selected (ELEMENTNAME_TYPE))
	SetChangedFlag (true);
      break;

    case F_SelectedElements:
      if (set_selected (ELEMENT_TYPE))
	SetChangedFlag (true);
      break;

    case F_Selected:
    case F_SelectedObjects:
      if (set_selected (CHANGESIZE_TYPES))
	SetChangedFlag (true);
      break;
    }
}

/* --------------------------------------------------------------------------- */

static const char executefile_syntax[] = N_("ExecuteFile(filename)");

static const char executefile_help[] = N_("Run actions from the given file.");

/* %start-doc actions ExecuteFile

Lines starting with @code{#} are ignored.

%end-doc */

static int
ActionExecuteFile (int argc, char **argv, Coord x, Coord y)
{
  FILE *fp;
  char *fname;
  char line[256];
  int n = 0;
  char *sp;

  if (argc != 1)
    AFAIL (executefile);

  fname = argv[0];

  if ((fp = fopen (fname, "r")) == NULL)
    {
      fprintf (stderr, _("Could not open actions file \"%s\".\n"), fname);
      return 1;
    }

  defer_updates = 1;
  defer_needs_update = 0;
  while (fgets (line, sizeof (line), fp) != NULL)
    {
      n++;
      sp = line;

      /* eat the trailing newline */
      while (*sp && *sp != '\r' && *sp != '\n')
	sp++;
      *sp = '\0';

      /* eat leading spaces and tabs */
      sp = line;
      while (*sp && (*sp == ' ' || *sp == '\t'))
	sp++;

      /* 
       * if we have anything left and its not a comment line
       * then execute it
       */

      if (*sp && *sp != '#')
	{
	  /*Message ("%s : line %-3d : \"%s\"\n", fname, n, sp);*/
	  hid_parse_actions (sp);
	}
    }

  defer_updates = 0;
  if (defer_needs_update)
    {
      IncrementUndoSerialNumber ();
      gui->invalidate_all ();
    }
  fclose (fp);
  return 0;
}

/* --------------------------------------------------------------------------- */

static int
ActionPSCalib (int argc, char **argv, Coord x, Coord y)
{
  HID *ps = hid_find_exporter ("ps");
  ps->calibrate (0.0,0.0);
  return 0;
}

/* --------------------------------------------------------------------------- */

static ElementType *element_cache = NULL;

static ElementType *
find_element_by_refdes (char *refdes)
{
  if (element_cache
      && NAMEONPCB_NAME(element_cache)
      && strcmp (NAMEONPCB_NAME(element_cache), refdes) == 0)
    return element_cache;

  ELEMENT_LOOP (PCB->Data);
  {
    if (NAMEONPCB_NAME(element)
	&& strcmp (NAMEONPCB_NAME(element), refdes) == 0)
      {
	element_cache = element;
	return element_cache;
      }
  }
  END_LOOP;
  return NULL;
}

static AttributeType *
lookup_attr (AttributeListType *list, const char *name)
{
  int i;
  for (i=0; i<list->Number; i++)
    if (strcmp (list->List[i].name, name) == 0)
      return & list->List[i];
  return NULL;
}

static void
delete_attr (AttributeListType *list, AttributeType *attr)
{
  int idx = attr - list->List;
  if (idx < 0 || idx >= list->Number)
    return;
  if (list->Number - idx > 1)
    memmove (attr, attr+1, (list->Number - idx - 1) * sizeof(AttributeType));
  list->Number --;
}

/* ---------------------------------------------------------------- */
static const char elementlist_syntax[] =
  N_("ElementList(Start|Done|Need,<refdes>,<footprint>,<value>)");

static const char elementlist_help[] =
  N_("Adds the given element if it doesn't already exist.");

/* %start-doc actions elementlist

@table @code

@item Start
Indicates the start of an element list; call this before any Need
actions.

@item Need
Searches the board for an element with a matching refdes.

If found, the value and footprint are updated.

If not found, a new element is created with the given footprint and value.

@item Done
Compares the list of elements needed since the most recent
@code{start} with the list of elements actually on the board.  Any
elements that weren't listed are selected, so that the user may delete
them.

@end table

%end-doc */

static int number_of_footprints_not_found;

static int
parse_layout_attribute_units (char *name, int def)
{
  const char *as = AttributeGet (PCB, name);
  if (!as)
    return def;
  return GetValue (as, NULL, NULL);
}

static int
ActionElementList (int argc, char **argv, Coord x, Coord y)
{
  ElementType *e = NULL;
  char *refdes, *value, *footprint, *old;
  char *args[3];
  char *function;

  if (argc < 1)
    AFAIL (elementlist);

  function = argv[0];

#ifdef DEBUG
  printf("Entered ActionElementList, executing function %s\n", function);
#endif

  if (strcasecmp (function, "start") == 0)
    {
      ELEMENT_LOOP (PCB->Data);
      {
	CLEAR_FLAG (FOUNDFLAG, element);
      }
      END_LOOP;
      element_cache = NULL;
      number_of_footprints_not_found = 0;
      return 0;
    }

  if (strcasecmp (function, "done") == 0)
    {
      ELEMENT_LOOP (PCB->Data);
      {
	if (TEST_FLAG (FOUNDFLAG, element))
	  {
	    CLEAR_FLAG (FOUNDFLAG, element);
	  }
	else if (! EMPTY_STRING_P (NAMEONPCB_NAME (element)))
	  {
	    /* Unnamed elements should remain untouched */
	    SET_FLAG (SELECTEDFLAG, element);
	  }
      }
      END_LOOP;
      if (number_of_footprints_not_found > 0)
	gui->confirm_dialog (_("Not all requested footprints were found.\n"
			     "See the message log for details"),
			     "Ok", NULL);
      return 0;
    }

  if (strcasecmp (function, "need") != 0)
    AFAIL (elementlist);

  if (argc != 4)
    AFAIL (elementlist);

  argc --;
  argv ++;

  refdes = ARG(0);
  footprint = ARG(1);
  value = ARG(2);

  args[0] = footprint;
  args[1] = refdes;
  args[2] = value;

#ifdef DEBUG
  printf("  ... footprint = %s\n", footprint);
  printf("  ... refdes = %s\n", refdes);
  printf("  ... value = %s\n", value);
#endif

  e = find_element_by_refdes (refdes);

  if (!e)
    {
      Coord nx, ny, d;

#ifdef DEBUG
      printf("  ... Footprint not on board, need to add it.\n");
#endif
      /* Not on board, need to add it. */
      if (LoadFootprint(argc, args, x, y))
	{
	  number_of_footprints_not_found ++;
	  return 1;
	}

      nx = PCB->MaxWidth / 2;
      ny = PCB->MaxHeight / 2;
      d = MIN (PCB->MaxWidth, PCB->MaxHeight) / 10;

      nx = parse_layout_attribute_units ("import::newX", nx);
      ny = parse_layout_attribute_units ("import::newY", ny);
      d = parse_layout_attribute_units ("import::disperse", d);

      if (d > 0)
	{
	  nx += rand () % (d*2) - d;
	  ny += rand () % (d*2) - d;
	}

      if (nx < 0)
	nx = 0;
      if (nx >= PCB->MaxWidth)
	nx = PCB->MaxWidth - 1;
      if (ny < 0)
	ny = 0;
      if (ny >= PCB->MaxHeight)
	ny = PCB->MaxHeight - 1;

      /* Place components onto center of board. */
      if (CopyPastebufferToLayout (nx, ny))
	SetChangedFlag (true);
    }

  else if (e && DESCRIPTION_NAME(e) && strcmp (DESCRIPTION_NAME(e), footprint) != 0)
    {
      int er, pr, i;
      Coord mx, my;
      ElementType *pe;

#ifdef DEBUG
      printf("  ... Footprint on board, but different from footprint loaded.\n");
#endif
      /* Different footprint, we need to swap them out.  */
      if (LoadFootprint(argc, args, x, y))
	{
	  number_of_footprints_not_found ++;
	  return 1;
	}

      er = ElementOrientation (e);
      pe = PASTEBUFFER->Data->Element->data;
      if (!FRONT (e))
	MirrorElementCoordinates (PASTEBUFFER->Data, pe, pe->MarkY*2 - PCB->MaxHeight);
      pr = ElementOrientation (pe);

      mx = e->MarkX;
      my = e->MarkY;

      if (er != pr)
	RotateElementLowLevel (PASTEBUFFER->Data, pe, pe->MarkX, pe->MarkY, (er-pr+4)%4);

      for (i=0; i<MAX_ELEMENTNAMES; i++)
	{
	  pe->Name[i].X = e->Name[i].X - mx + pe->MarkX ;
	  pe->Name[i].Y = e->Name[i].Y - my + pe->MarkY ;
	  pe->Name[i].Direction = e->Name[i].Direction;
	  pe->Name[i].Scale = e->Name[i].Scale;
	}

      RemoveElement (e);

      if (CopyPastebufferToLayout (mx, my))
	SetChangedFlag (true);
    }

  /* Now reload footprint */
  element_cache = NULL;
  e = find_element_by_refdes (refdes);

  old = ChangeElementText (PCB, PCB->Data, e, NAMEONPCB_INDEX, strdup (refdes));
  if (old)
    free(old);
  old = ChangeElementText (PCB, PCB->Data, e, VALUE_INDEX, strdup (value));
  if (old)
    free(old);

  SET_FLAG (FOUNDFLAG, e);

#ifdef DEBUG
  printf(" ... Leaving ActionElementList.\n");
#endif

  return 0;
}

/* ---------------------------------------------------------------- */
static const char elementsetattr_syntax[] =
  N_("ElementSetAttr(refdes,name[,value])");

static const char elementsetattr_help[] =
  N_("Sets or clears an element-specific attribute.");

/* %start-doc actions elementsetattr

If a value is specified, the named attribute is added (if not already
present) or changed (if it is) to the given value.  If the value is
not specified, the given attribute is removed if present.

%end-doc */

static int
ActionElementSetAttr (int argc, char **argv, Coord x, Coord y)
{
  ElementType *e = NULL;
  char *refdes, *name, *value;
  AttributeType *attr;

  if (argc < 2)
    {
      AFAIL (elementsetattr);
    }

  refdes = argv[0];
  name = argv[1];
  value = ARG(2);

  ELEMENT_LOOP (PCB->Data);
  {
    if (NSTRCMP (refdes, NAMEONPCB_NAME (element)) == 0)
      {
	e = element;
	break;
      }
  }
  END_LOOP;

  if (!e)
    {
      Message(_("Cannot change attribute of %s - element not found\n"), refdes);
      return 1;
    }

  attr = lookup_attr (&e->Attributes, name);

  if (attr && value)
    {
      free (attr->value);
      attr->value = strdup (value);
    }
  if (attr && ! value)
    {
      delete_attr (& e->Attributes, attr);
    }
  if (!attr && value)
    {
      CreateNewAttribute (& e->Attributes, name, value);
    }

  return 0;
}

/* ---------------------------------------------------------------- */
static const char execcommand_syntax[] = N_("ExecCommand(command)");

static const char execcommand_help[] = N_("Runs a command.");

/* %start-doc actions execcommand

Runs the given command, which is a system executable.

%end-doc */

static int
ActionExecCommand (int argc, char **argv, Coord x, Coord y)
{
  char *command;

  if (argc < 1)
    {
      AFAIL (execcommand);
    }

  command = ARG(0);

  if (system (command))
    return 1;
  return 0;
}

/* ---------------------------------------------------------------- */

static int
pcb_spawnvp (char **argv)
{
#ifdef HAVE__SPAWNVP
  int result = _spawnvp (_P_WAIT, argv[0], (const char * const *) argv);
  if (result == -1)
    return 1;
  else
    return 0;
#else
  int pid;
  pid = fork ();
  if (pid < 0)
    {
      /* error */
      Message(_("Cannot fork!"));
      return 1;
    }
  else if (pid == 0)
    {
      /* Child */
      execvp (argv[0], argv);
      exit(1);
    }
  else
    {
      int rv;
      /* Parent */
      wait (&rv);
    }
  return 0;
#endif
}

/* ---------------------------------------------------------------- */

/*! 
 * \brief Creates a new temporary file name.
 * 
 * Hopefully the operating system provides a mkdtemp() function to
 * securily create a temporary directory with mode 0700.\n
 * If so then that directory is created and the returned string is made
 * up of the directory plus the name variable.\n
 * For example:\n
 *
 * tempfile_name_new ("myfile") might return
 * "/var/tmp/pcb.123456/myfile".
 *
 * If mkdtemp() is not available then 'name' is ignored and the
 * insecure tmpnam() function is used.
 *  
 * Files/names created with tempfile_name_new() should be unlinked
 * with tempfile_unlink to make sure the temporary directory is also
 * removed when mkdtemp() is used.
 */
static char *
tempfile_name_new (char * name)
{
  char *tmpfile = NULL;
#ifdef HAVE_MKDTEMP
  char *tmpdir, *mytmpdir;
  size_t len;
#endif

  assert ( name != NULL );

#ifdef HAVE_MKDTEMP
#define TEMPLATE "pcb.XXXXXXXX"
    
  
  tmpdir = getenv ("TMPDIR");

  /* FIXME -- what about win32? */
  if (tmpdir == NULL) {
    tmpdir = "/tmp";
  }
  
  mytmpdir = (char *) malloc (sizeof(char) * 
			      (strlen (tmpdir) + 
			       1 +
			       strlen (TEMPLATE) + 
			       1));
  if (mytmpdir == NULL) {
    fprintf (stderr, "%s(): malloc failed()\n", __FUNCTION__);
    exit (1);
  }
  
  *mytmpdir = '\0';
  (void)strcat (mytmpdir, tmpdir);
  (void)strcat (mytmpdir, PCB_DIR_SEPARATOR_S);
  (void)strcat (mytmpdir, TEMPLATE);
  if (mkdtemp (mytmpdir) == NULL) {
    fprintf (stderr, "%s():  mkdtemp (\"%s\") failed\n", __FUNCTION__, mytmpdir);
    free (mytmpdir);
    return NULL;
  }


  len = strlen (mytmpdir) + /* the temp directory name */
    1 +                     /* the directory sep. */
    strlen (name) +         /* the file name */
    1                       /* the \0 termination */
    ;

  tmpfile = (char *) malloc (sizeof (char) * len);

  *tmpfile = '\0';
  (void)strcat (tmpfile, mytmpdir);
  (void)strcat (tmpfile, PCB_DIR_SEPARATOR_S);
  (void)strcat (tmpfile, name);
  
  free (mytmpdir);
#undef TEMPLATE
#else
  /*
   * tmpnam() uses a static buffer so strdup() the result right away
   * in case someone decides to create multiple temp names.
   */
  tmpfile = strdup (tmpnam (NULL));
#ifdef __WIN32__
    {
      /* Guile doesn't like \ separators */
      char *c;
      for (c = tmpfile; *c; c++)
	if (*c == '\\')
	  *c = '/';
    }
#endif
#endif

  return tmpfile;
}

/* ---------------------------------------------------------------- */

/*!
 * \brief Unlink a temporary file.
 * 
 * If we have mkdtemp() then our temp file lives in a temporary
 * directory and we need to remove that directory too.
 */
static int
tempfile_unlink (char * name)
{
#ifdef DEBUG
    /* SDB says:  Want to keep old temp files for examiniation when debugging */
  return 0;
#else /* DEBUG */

#ifdef HAVE_MKDTEMP
  int e, rc2 = 0;
  char *dname;

  unlink (name);
  /* it is possible that the file was never created so it is OK if the
     unlink fails */

  /* now figure out the directory name to remove */
  e = strlen (name) - 1;
  while (e > 0 && name[e] != PCB_DIR_SEPARATOR_C) {e--;}
  
  dname = strdup (name);
  dname[e] = '\0';

  /* 
   * at this point, e *should* point to the end of the directory part 
   * but lets make sure.
   */
  if (e > 0) {
    rc2 = rmdir (dname);
    if (rc2 != 0) {
      perror (dname);
    }

  } else {
    fprintf (stderr, _("%s():  Unable to determine temp directory name from the temp file\n"),
	     __FUNCTION__);
    fprintf (stderr, "%s():  \"%s\"\n", 
	     __FUNCTION__, name);
    rc2 = -1;
  }

  /* name was allocated with malloc */
  free (dname);
  free (name);

  /*
   * FIXME - should also return -1 if the temp file exists and was not
   * removed.  
   */
  if (rc2 != 0) {
    return -1;
  }

#else /* HAVE_MKDTEMP */
  int rc = unlink (name);

  if (rc != 0) {
    fprintf (stderr, _("Failed to unlink \"%s\"\n"), name);
    free (name);
    return rc;
  }
  free (name);

#endif /* HAVE_MKDTEMP */
#endif /* DEBUG */

  return 0;
}

/* ---------------------------------------------------------------- */
static const char tcad_import_syntax[] =
  N_("ImportTinyCAD()\n"
  "ImportTinyCAD(netlistfile)\n");

static const char tcad_import_help[] = N_("Import schematics from TinyCAD.");

/* %start-doc actions ImportTinyCAD

Imports netlist and parts from the TinyCAD. TinyCAD allows to export
netlist in gEDA compatible format and part list in standard CSV format.

The footprints should be defined as parameters of TinyCAD symbols.
@code{Package} and @code{Footprint} parameters can be used, @code{Footprint} parameter has priority.

Netlist and partlist files should have the same base name with @code{.net} and @code{.csv} extensions.
During import only the netlist filename can be specified, parlist filename is derived from netlist
filename by replacing @code{.net} extension by @code{.csv} extension or by adding @code{.csv} extension
if netlist file does not have @code{.net} extension.

@table @code

@item ImportTinyCAD()

Prompts the user to select netlist file. The netlist is imported, followed by partlist import.
Parts are imported by sequence of @code{ElementList} actions. If existing schematics is being updated,
existing parts are updated, new parts are added, removed parts are pre-selected to be easily
deleted by user.

@item ImportTinyCAD(netlistfile)

Same as above, but specified file is used as netlist filename.

@end table

%end-doc */


#define CSVLEN	4096

static int
ActionImportTinyCAD (int argc, char **argv, Coord x, Coord y)
{

  netlist_loaded = false;

  if (argc < 2 )
    {
      hid_actionl ("Load", "Netlist", NULL);
    }
  else
    {
      hid_actionl ("LoadFrom", "Netlist", argv[1], NULL);
    }

  if (netlist_loaded)
    {
      int l = strlen (PCB->Netlistname);
      char *s, *s2, *csvname = alloca(l+5);
      char line[CSVLEN];
      FILE *f;
      bool header = TRUE;
      bool first_entry = TRUE;
      int maxhdr;
      int ix;
      int rhdr = -1,
          vhdr = -1,
	  fhdr = -1,
	  phdr = -1;
      char *rs, *vs, *fs, *ps;

      if (csvname == NULL)
          return 0;

      strcpy (csvname, PCB->Netlistname);
      if (l > 4 && strcasecmp (csvname+l-4, ".net") == 0)
	  csvname[l-4] = '\0';
      strcat(csvname, ".csv");

      Message ("Importing TinyCAD Parts file (CSV): %s\n", csvname);

      f = fopen (csvname, "r");
      if (f == NULL)
        return 0;

      fgets (line, sizeof(line), f);

      do {
        if((s = strchr (line, '\r')) != NULL)
          *s = '\0';
        if((s = strchr (line, '\n')) != NULL)
          *s = '\0';
        if (header)
          {
	    /* Parse header line, no quotes expcted */
	    ix = 0;
	    s = strtok (line, ",");
	    while (s != NULL)
	      {
	        if (strcasecmp (s, "Reference") == 0)
	          rhdr = ix;
	        else if (strcasecmp (s, "Value") == 0)
	          vhdr = ix;
	        else if (strcasecmp (s, "Footprint") == 0)
	          fhdr = ix;
	        else if (strcasecmp (s, "Package") == 0)
	          phdr = ix;

	        s  = strtok (NULL, ",");
	        ix++;
	      }
	    if (rhdr == -1 || (fhdr == -1 && phdr == -1))
	      {
	        Message ("Missing Reference and/or Footprint or Package column. Part list cannot be imported.\n");
	        return 0;
	      }
	    header = false;
	    maxhdr = max (rhdr, max (vhdr, max (fhdr, phdr)));
	  }
        else
          {
	    s = line;
	    ix = 0;
	    rs = NULL;
	    vs = NULL;
	    fs = NULL;
	    ps = NULL;

	    while (s != NULL)
	      {
	        if (*s == '"')
	          {
		    s2 = strstr (s,"\",");
		    if (s2 != NULL)
		      {
		        /* remove quote and move end pointer to conmma */
		        *s2 = '\0';
		        s2++;
		      }
		    else
		      {
		        s2 = strchr (s, '"');
		      }
		    if (s2 != NULL)
		      {
		        /* skip leading quote */
		        s++;
		      }
	          }
	        else
	          s2 = strchr (s, ',');

	        if (s2 != NULL)
	          {
	            *s2 = '\0';
		    s2++;
		  }

	        if (ix == rhdr)
	          rs = s;
	        else if (ix == vhdr)
	          vs = s;
	        else if (ix == fhdr)
	          fs = s;
	        else if (ix == phdr)
	          ps = s;

                if (ix == maxhdr)
	          break;

	        s =  s2;
	        ix++;
	      }

	    if (ix == maxhdr)
	      {
	        char *afs;

		if (fs != NULL && strcmp (fs, "..") != 0 && strlen (fs) > 0)
		  afs = fs;
		else if (ps != NULL && strcmp (ps, "..") != 0 && strlen (ps) > 0)
		  afs = ps;
		else
		  afs = NULL;

		if (afs != NULL)
		  {
		    if (strcmp (vs, "..") == 0)
		      vs = "";

	            s = strtok (rs, ",");
	            while (s != NULL)
	              {
#ifdef DEBUG
		        Message ("Importing element: Refdes: \"%s\" - Value: \"%s\" - Footprint: \"%s\"\n", s, vs, afs);
#endif
                        if (first_entry)
			  {
			    hid_actionl("ElementList","Start", NULL);
			    first_entry = FALSE;
			  }
			hid_actionl("ElementList","Need", s, afs, vs, NULL);
	                s  = strtok (NULL, ",");
	              }
		  }
	        else
	          Message ("Element(s) \"%s\" have no Footprint or Package attribute. They cannot be imported.\n", rs);
	      }
	  }

        fgets (line, sizeof (line), f);
      } while (!feof (f));
      fclose (f);

      if (!first_entry)
        {
          hid_actionl("ElementList","Done", NULL);
        }
  }
  return 0;

}

/* ---------------------------------------------------------------- */
static const char import_syntax[] =
  N_("Import()\n"
  "Import([gnetlist|make[,source,source,...]])\n"
  "Import(setnewpoint[,(mark|center|X,Y)])\n"
  "Import(setdisperse,D,units)\n");

static const char import_help[] = N_("Import schematics.");

/* %start-doc actions Import

Imports element and netlist data from the schematics (or some other
source).  The first parameter, which is optional, is the mode.  If not
specified, the @code{import::mode} attribute in the PCB is used.
@code{gnetlist} means gnetlist is used to obtain the information from
the schematics.  @code{make} invokes @code{make}, assuming the user
has a @code{Makefile} in the current directory.  The @code{Makefile}
will be invoked with the following variables set:

@table @code

@item PCB
The name of the .pcb file

@item SRCLIST
A space-separated list of source files

@item OUT
The name of the file in which to put the command script, which may
contain any @pcb{} actions.  By default, this is a temporary file
selected by @pcb{}, but if you specify an @code{import::outfile}
attribute, that file name is used instead (and not automatically
deleted afterwards).

@end table

The target specified to be built is the first of these that apply:

@itemize @bullet

@item
The target specified by an @code{import::target} attribute.

@item
The output file specified by an @code{import::outfile} attribute.

@item
If nothing else is specified, the target is @code{pcb_import}.

@end itemize

If you specify an @code{import::makefile} attribute, then "-f <that
file>" will be added to the command line.

If you specify the mode, you may also specify the source files
(schematics).  If you do not specify any, the list of schematics is
obtained by reading the @code{import::src@var{N}} attributes (like
@code{import::src0}, @code{import::src1}, etc).

For compatibility with future extensions to the import file format,
the generated file @emph{must not} start with the two characters
@code{#%}.

If a temporary file is needed the @code{TMPDIR} environment variable
is used to select its location.

Note that the programs @code{gnetlist} and @code{make} may be
overridden by the user via the @code{make-program} and @code{gnetlist}
@code{pcb} settings (i.e. in @code{~/.pcb/settings} or on the command
line).

If @pcb{} cannot determine which schematic(s) to import from, the GUI
is called to let user choose (see @code{ImportGUI()}).

Note that Import() doesn't delete anything - after an Import, elements
which shouldn't be on the board are selected and may be removed once
it's determined that the deletion is appropriate.

If @code{Import()} is called with @code{setnewpoint}, then the location
of new components can be specified.  This is where parts show up when
they're added to the board.  The default is the center of the board.

@table @code

@item Import(setnewpoint)

Prompts the user to click on the board somewhere, uses that point.  If
called by a hotkey, uses the current location of the crosshair.

@item Import(setnewpoint,mark)

Uses the location of the mark.  If no mark is present, the point is
not changed.

@item Import(setnewpoint,center)

Resets the point to the center of the board.

@item Import(setnewpoint,X,Y,units)

Sets the point to the specific coordinates given.  Example:
@code{Import(setnewpoint,50,25,mm)}

@end table

Note that the X and Y locations are stored in attributes named
@code{import::newX} and @code{import::newY} so you could change them
manually if you wished.

Calling @code{Import(setdisperse,D,units)} sets how much the newly
placed elements are dispersed relative to the set point.  For example,
@code{Import(setdisperse,10,mm)} will offset each part randomly up to
10mm away from the point.  The default dispersion is 1/10th of the
smallest board dimension.  Dispersion is saved in the
@code{import::disperse} attribute.

%end-doc */

static int
ActionImport (int argc, char **argv, Coord x, Coord y)
{
  char *mode;
  char **sources = NULL;
  int nsources = 0;

#ifdef DEBUG
      printf("ActionImport:  ===========  Entering ActionImport  ============\n");
#endif

  mode = ARG (0);

  if (mode && strcasecmp (mode, "setdisperse") == 0)
    {
      char *ds, *units;
      char buf[50];

      ds = ARG (1);
      units = ARG (2);
      if (!ds)
	{
	  const char *as = AttributeGet (PCB, "import::disperse");
	  ds = gui->prompt_for(_("Enter dispersion:"), as ? as : "0");
	}
      if (units)
	{
	  sprintf(buf, "%s%s", ds, units);
	  AttributePut (PCB, "import::disperse", buf);
	}
      else
	AttributePut (PCB, "import::disperse", ds);
      if (ARG (1) == NULL)
        free (ds);
      return 0;
    }

  if (mode && strcasecmp (mode, "setnewpoint") == 0)
    {
      const char *xs, *ys, *units;
      Coord x, y;
      char buf[50];

      xs = ARG (1);
      ys = ARG (2);
      units = ARG (3);

      if (!xs)
	{
	  gui->get_coords (_("Click on a location"), &x, &y);
	}
      else if (strcasecmp (xs, "center") == 0)
	{
	  AttributeRemove (PCB, "import::newX");
	  AttributeRemove (PCB, "import::newY");
	  return 0;
	}
      else if (strcasecmp (xs, "mark") == 0)
	{
	  if (!Marked.status)
	    return 0;

	  x = Marked.X;
	  y = Marked.Y;
	}
      else if (ys)
	{
	  x = GetValue (xs, units, NULL);
	  y = GetValue (ys, units, NULL);
	}
      else
	{
	  Message (_("Bad syntax for Import(setnewpoint)"));
	  return 1;
	}

      pcb_snprintf (buf, sizeof (buf), "%$ms", x);
      AttributePut (PCB, "import::newX", buf);
      pcb_snprintf (buf, sizeof (buf), "%$ms", y);
      AttributePut (PCB, "import::newY", buf);
      return 0;
    }

  if (! mode)
    mode = AttributeGet (PCB, "import::mode");
  if (! mode)
    mode = "gnetlist";

  if (argc > 1)
    {
      sources = argv + 1;
      nsources = argc - 1;
    }

  if (! sources)
    {
      char sname[40];
      char *src;

      nsources = -1;
      do {
	nsources ++;
	sprintf(sname, "import::src%d", nsources);
	src = AttributeGet (PCB, sname);
      } while (src);

      if (nsources > 0)
	{
	  sources = (char **) malloc ((nsources + 1) * sizeof (char *));
	  nsources = -1;
	  do {
	    nsources ++;
	    sprintf(sname, "import::src%d", nsources);
	    src = AttributeGet (PCB, sname);
	    sources[nsources] = src;
	  } while (src);
	}
    }

  if (! sources)
    {
      /* Replace .pcb with .sch and hope for the best.  */
      char *pcbname = PCB->Filename;
      char *schname;
      char *dot, *slash, *bslash;

      if (!pcbname)
	return hid_action("ImportGUI");

      schname = (char *) malloc (strlen(pcbname) + 5);
      strcpy (schname, pcbname);
      dot = strchr (schname, '.');
      slash = strchr (schname, '/');
      bslash = strchr (schname, '\\');
      if (dot && slash && dot < slash)
	dot = NULL;
      if (dot && bslash && dot < bslash)
	dot = NULL;
      if (dot)
	*dot = 0;
      strcat (schname, ".sch");

      if (access (schname, F_OK))
        {
          free (schname);
          return hid_action("ImportGUI");
        }

      sources = (char **) malloc (2 * sizeof (char *));
      sources[0] = schname;
      sources[1] = NULL;
      nsources = 1;
    }

  if (strcasecmp (mode, "gnetlist") == 0)
    {
      char *tmpfile = tempfile_name_new ("gnetlist_output");
      char **cmd;
      int i;

      if (tmpfile == NULL) {
	Message (_("Could not create temp file"));
	return 1;
      }

      cmd = (char **) malloc ((7 + nsources) * sizeof (char *));
      cmd[0] =  Settings.GnetlistProgram;
      cmd[1] = "-g";
      cmd[2] = "pcbfwd";
      cmd[3] = "-o";
      cmd[4] = tmpfile;
      cmd[5] = "--";
      for (i=0; i<nsources; i++)
	cmd[6+i] = sources[i];
      cmd[6+nsources] = NULL;

#ifdef DEBUG
      printf("ActionImport:  ===========  About to run gnetlist  ============\n");
      printf("%s %s %s %s %s %s %s ...\n", 
	     cmd[0], cmd[1], cmd[2], cmd[3], cmd[4], cmd[5], cmd[6]);
#endif

      if (pcb_spawnvp (cmd))
	{
	  unlink (tmpfile);
	  return 1;
	}

#ifdef DEBUG
      printf("ActionImport:  ===========  About to run ActionExecuteFile, file = %s  ============\n", tmpfile);
#endif

      cmd[0] = tmpfile;
      cmd[1] = NULL;
      ActionExecuteFile (1, cmd, 0, 0);

      free (cmd);
      tempfile_unlink (tmpfile);
    }
  else if (strcasecmp (mode, "make") == 0)
    {
      int must_free_tmpfile = 0;
      char *tmpfile;
      char *cmd[10];
      int i;
      char *srclist;
      int srclen;
      char *user_outfile = NULL;
      char *user_makefile = NULL;
      char *user_target = NULL;


      user_outfile = AttributeGet (PCB, "import::outfile");
      user_makefile = AttributeGet (PCB, "import::makefile");
      user_target = AttributeGet (PCB, "import::target");
      if (user_outfile && !user_target)
	user_target = user_outfile;

      if (user_outfile)
	tmpfile = user_outfile;
      else
	{
	  tmpfile = tempfile_name_new ("gnetlist_output");
	  if (tmpfile == NULL) {
	    Message (_("Could not create temp file"));
            free (sources);
	    return 1;
	  }
	  must_free_tmpfile = 1;
	}

      srclen = sizeof("SRCLIST=") + 2;
      for (i=0; i<nsources; i++)
	srclen += strlen (sources[i]) + 2;
      srclist = (char *) malloc (srclen);
      strcpy (srclist, "SRCLIST=");
      for (i=0; i<nsources; i++)
	{
	  if (i)
	    strcat (srclist, " ");
	  strcat (srclist, sources[i]);
	}
      
      cmd[0] = Settings.MakeProgram;
      cmd[1] = "-s";
      cmd[2] = Concat ("PCB=", PCB->Filename, NULL);
      cmd[3] = srclist;
      cmd[4] = Concat ("OUT=", tmpfile, NULL);
      i = 5;
      if (user_makefile)
	{
	  cmd[i++] = "-f";
	  cmd[i++] = user_makefile;
	}
      cmd[i++] = user_target ? user_target : (char *)"pcb_import";
      cmd[i++] = NULL;

      if (pcb_spawnvp (cmd))
	{
	  if (must_free_tmpfile)
	    unlink (tmpfile);
	  free (cmd[2]);
	  free (cmd[3]);
	  free (cmd[4]);
	  return 1;
	}

      cmd[0] = tmpfile;
      cmd[1] = NULL;
      ActionExecuteFile (1, cmd, 0, 0);

      free (cmd[2]);
      free (cmd[3]);
      free (cmd[4]);
      if (must_free_tmpfile)
	tempfile_unlink (tmpfile);
    }
  else
    {
      Message (_("Unknown import mode: %s\n"), mode);
      return 1;
    }

  DeleteRats (false);
  AddAllRats (false, NULL);

#ifdef DEBUG
      printf("ActionImport:  ===========  Leaving ActionImport  ============\n");
#endif

  return 0;
}

/* ------------------------------------------------------------ */

static const char attributes_syntax[] =
  N_("Attributes(Layout|Layer|Element)\n"
  "Attributes(Layer,layername)");

static const char attributes_help[] =
  N_("Let the user edit the attributes of the layout, current or given\n"
  "layer, or selected element.");

/* %start-doc actions Attributes

This just pops up a dialog letting the user edit the attributes of the
pcb, an element, or a layer.

%end-doc */


static int
ActionAttributes (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  char *layername = ARG (1);
  char *buf;

  if (!function)
    AFAIL (attributes);

  if (!gui->edit_attributes)
    {
      Message (_("This GUI doesn't support Attribute Editing\n"));
      return 1;
    }

  switch (GetFunctionID (function))
    {
    case F_Layout:
      {
	gui->edit_attributes(_("Layout Attributes"), &(PCB->Attributes));
	return 0;
      }

    case F_Layer:
      {
	LayerType *layer = CURRENT;
	if (layername)
	  {
	    int i;
	    layer = NULL;
	    for (i=0; i<max_copper_layer; i++)
	      if (strcmp (PCB->Data->Layer[i].Name, layername) == 0)
		{
		  layer = & (PCB->Data->Layer[i]);
		  break;
		}
	    if (layer == NULL)
	      {
		Message (_("No layer named %s\n"), layername);
		return 1;
	      }
	  }
	buf = (char *) malloc (strlen (layer->Name) +
	    strlen (_("Layer %s Attributes")));
	sprintf (buf, _("Layer %s Attributes"), layer->Name);
	gui->edit_attributes(buf, &(layer->Attributes));
	free (buf);
	return 0;
      }

    case F_Element:
      {
	int n_found = 0;
	ElementType *e = NULL;
	ELEMENT_LOOP (PCB->Data);
	{
	  if (TEST_FLAG (SELECTEDFLAG, element))
	    {
	      e = element;
	      n_found ++;
	    }
	}
	END_LOOP;
	if (n_found > 1)
	  {
	    Message (_("Too many elements selected\n"));
	    return 1;
	  }
	if (n_found == 0)
	  {
	    void *ptrtmp;
	    gui->get_coords (_("Click on an element"), &x, &y);
	    if ((SearchScreen
		 (x, y, ELEMENT_TYPE, &ptrtmp,
		  &ptrtmp, &ptrtmp)) != NO_TYPE)
	      e = (ElementType *) ptrtmp;
	    else
	      {
		Message (_("No element found there\n"));
		return 1;
	      }
	  }

	if (NAMEONPCB_NAME(e))
	  {
	    buf = (char *) malloc (strlen (NAMEONPCB_NAME(e)) +
		strlen (_("Element %s Attributes")));
	    sprintf(buf, _("Element %s Attributes"), NAMEONPCB_NAME(e));
	  }
	else
	  {
	    buf = strdup (_("Unnamed Element Attributes"));
	  }
	gui->edit_attributes(buf, &(e->Attributes));
	free (buf);
	break;
      }

    default:
      AFAIL (attributes);
    }

  return 0;
}

/* --------------------------------------------------------------------------- */

static const char setvialayers_syntax[] =
  N_("SetViaLayers(Object|SelectedVias|Selected[,ThroughHole|TH])\n"
     "SetViaLayers(Object|SelectedVias|Selected,from,to)\n"
     "SetViaLayers(Object|SelectedVias|Selected,[c|-|from],[c|-|to])"
     );

static const char setvialayers_help[] =
  N_("Sets starting and ending layer for burried/blind/standard vias.");

/* %start-doc actions setvialayers

Specifies layers, which are connected by via.

@table @code

@item TH|ThroughHole
The vias will be set as through-hole, connecting all layers

@item from
layer name or layer number of the first layer to be connected by via; "-" stands for unchanged, "c" stands for currently selected layer

@item to
layer name or layer number of the last layer to be connected by via; "-" stands for unchanged, "c" stands for currently selected layer

@end table

If no parameter us used, dialog is displayed (if implemented in the respective GUI HID).


%end-doc */

static bool
identify_layer (char *layer_name, Cardinal *layer_no)
{
  int layer;

  if (strcmp (layer_name, "-") == 0)
    {
      *layer_no = -1;
      return true;
    }

  if (strcmp (layer_name, "c") == 0)
    {
      if ((unsigned int)INDEXOFCURRENT < max_copper_layer)
        {
          *layer_no = INDEXOFCURRENT;
          return true;
        }
    }

  layer = SearchLayerByName (PCB->Data, layer_name);
  if (layer == -1)
    {
      if (sscanf (layer_name, "%d", &layer) != 1)
        layer = -1;
    }

  if (layer != -1)
    *layer_no = layer;

  return (layer != -1);
}

static int
ActionSetViaLayers (int argc, char **argv, Coord x, Coord y)
{
  char *function = ARG (0);
  char *layername_from = ARG (1);
  char *layername_to = ARG (2);
  Cardinal layer_from ;
  Cardinal layer_to = -1;

  if (!function)
    AFAIL (setvialayers);

  if ( /* !gui->edit_attributes  &&*/ argc < 2)
    {
      Message (_("This GUI doesn't support Via Layers editing\n"));
      return 1;
    }

  if (GetFunctionID (layername_from) == F_ThroughHole)
    {
      layer_from = 0;
      layer_to = 0;
    }
  else
    {
      if (!identify_layer (layername_from, &layer_from)
          || !identify_layer (layername_to, &layer_to))
	{
	  Message (_("Sorry, wrong layers specified.\n"));
          return 1;
	}
    }

  /* ensure that layer_from < layer_to */
  if (layer_from != -1
      && layer_to != -1
      && layer_from > layer_to)
    {
      int tmp;

      tmp = layer_from;
      layer_from = layer_to;
      layer_to = tmp;
    }

  if (layer_to != -1)
    layer_to = min (layer_to, max_copper_layer-1);

  switch (GetFunctionID (function))
    {
    case F_Object:
      {
	int type;
	void *ptr1, *ptr2, *ptr3;

	if ((type =
	     SearchScreen (Crosshair.X, Crosshair.Y, VIA_TYPE,
			   &ptr1, &ptr2, &ptr3)) != NO_TYPE)
	  {
	    if (TEST_FLAG (LOCKFLAG, (PinType *) ptr1))
	      Message (_("Sorry, the object is locked\n"));
	    else
	      {
	        if (ChangeObjectViaLayers (ptr1, ptr2, ptr3, layer_from, layer_to))
		  {
		    SetChangedFlag (true);
		  }
	      }
	  }
	break;
    case F_SelectedVias:
    case F_Selected:
	if (ChangeSelectedViaLayers (layer_from, layer_to))
	  {
	    SetChangedFlag (true);
	  }
	break;
      }
  }

  return 0;
}
/* --------------------------------------------------------------------------- */

HID_Action action_action_list[] = {
  {"AddRats", 0, ActionAddRats,
   addrats_help, addrats_syntax}
  ,
  {"Attributes", 0, ActionAttributes,
   attributes_help, attributes_syntax}
  ,
  {"Atomic", 0, ActionAtomic,
   atomic_help, atomic_syntax}
  ,
  {"AutoPlaceSelected", 0, ActionAutoPlaceSelected,
   autoplace_help, autoplace_syntax}
  ,
  {"AutoRoute", 0, ActionAutoRoute,
   autoroute_help, autoroute_syntax}
  ,
  {"ChangeClearSize", 0, ActionChangeClearSize,
   changeclearsize_help, changeclearsize_syntax}
  ,
  {"ChangeDrillSize", 0, ActionChange2ndSize,
   changedrillsize_help, changedrillsize_syntax}
  ,
  {"ChangeHole", 0, ActionChangeHole,
   changehold_help, changehold_syntax}
  ,
  {"ChangeJoin", 0, ActionChangeJoin,
   changejoin_help, changejoin_syntax}
  ,
  {"ChangeName", 0, ActionChangeName,
   changename_help, changename_syntax}
  ,
  {"ChangePaste", 0, ActionChangePaste,
   changepaste_help, changepaste_syntax}
  ,
  {"ChangePinName", 0, ActionChangePinName,
   changepinname_help, changepinname_syntax}
  ,
  {"ChangeSize", 0, ActionChangeSize,
   changesize_help, changesize_syntax}
  ,
  {"ChangeSquare", 0, ActionChangeSquare,
   changesquare_help, changesquare_syntax}
  ,
  {"ChangeOctagon", 0, ActionChangeOctagon,
   changeoctagon_help, changeoctagon_syntax}
  ,
  {"ClearSquare", 0, ActionClearSquare,
   clearsquare_help, clearsquare_syntax}
  ,
  {"ClearOctagon", 0, ActionClearOctagon,
   clearoctagon_help, clearoctagon_syntax}
  ,
  {"Connection", 0, ActionConnection,
   connection_help, connection_syntax}
  ,
  {"Delete", 0, ActionDelete,
   delete_help, delete_syntax}
  ,
  {"DeleteRats", 0, ActionDeleteRats,
   deleterats_help, deleterats_syntax}
  ,
  {"DisperseElements", 0, ActionDisperseElements,
   disperseelements_help, disperseelements_syntax}
  ,
  {"Display", 0, ActionDisplay,
   display_help, display_syntax}
  ,
  {"DumpLibrary", 0, ActionDumpLibrary,
   dumplibrary_help, dumplibrary_syntax}
  ,
  {"ExecuteFile", 0, ActionExecuteFile,
   executefile_help, executefile_syntax}
  ,
  {"Flip", N_("Click on Object or Flip Point"), ActionFlip,
   flip_help, flip_syntax}
  ,
  {"LoadFrom", 0, ActionLoadFrom,
   loadfrom_help, loadfrom_syntax}
  ,
  {"MarkCrosshair", 0, ActionMarkCrosshair,
   markcrosshair_help, markcrosshair_syntax}
  ,
  {"Message", 0, ActionMessage,
   message_help, message_syntax}
  ,
  {"MinMaskGap", 0, ActionMinMaskGap,
   minmaskgap_help, minmaskgap_syntax}
  ,
  {"MinClearGap", 0, ActionMinClearGap,
   mincleargap_help, mincleargap_syntax}
  ,
  {"Mode", 0, ActionMode,
   mode_help, mode_syntax}
  ,
  {"MorphPolygon", 0, ActionMorphPolygon,
   morphpolygon_help, morphpolygon_syntax}
  ,
  {"PasteBuffer", 0, ActionPasteBuffer,
   pastebuffer_help, pastebuffer_syntax}
  ,
  {"Quit", 0, ActionQuit,
   quit_help, quit_syntax}
  ,
  {"RemoveSelected", 0, ActionRemoveSelected,
   removeselected_help, removeselected_syntax}
  ,
  {"Renumber", 0, ActionRenumber,
   renumber_help, renumber_syntax}
  ,
  {"RipUp", 0, ActionRipUp,
   ripup_help, ripup_syntax}
  ,
  {"Select", 0, ActionSelect,
   select_help, select_syntax}
  ,
  {"Unselect", 0, ActionUnselect,
   unselect_help, unselect_syntax}
  ,
  {"SaveSettings", 0, ActionSaveSettings,
   savesettings_help, savesettings_syntax}
  ,
  {"SaveTo", 0, ActionSaveTo,
   saveto_help, saveto_syntax}
  ,
  {"SetSquare", 0, ActionSetSquare,
   setsquare_help, setsquare_syntax}
  ,
  {"SetOctagon", 0, ActionSetOctagon,
   setoctagon_help, setoctagon_syntax}
  ,
  {"SetThermal", 0, ActionSetThermal,
   setthermal_help, setthermal_syntax}
  ,
  {"SetValue", 0, ActionSetValue,
   setvalue_help, setvalue_syntax}
  ,
  {"ToggleHideName", 0, ActionToggleHideName,
   togglehidename_help, togglehidename_syntax}
  ,
  {"Undo", 0, ActionUndo,
   undo_help, undo_syntax}
  ,
  {"Redo", 0, ActionRedo,
   redo_help, redo_syntax}
  ,
  {"SetSame", N_("Select item to use attributes from"), ActionSetSame,
   setsame_help, setsame_syntax}
  ,
  {"SetFlag", 0, ActionSetFlag,
   setflag_help, setflag_syntax}
  ,
  {"ClrFlag", 0, ActionClrFlag,
   clrflag_help, clrflag_syntax}
  ,
  {"ChangeFlag", 0, ActionChangeFlag,
   changeflag_help, changeflag_syntax}
  ,
  {"Polygon", 0, ActionPolygon,
   polygon_help, polygon_syntax}
  ,
  {"RouteStyle", 0, ActionRouteStyle,
   routestyle_help, routestyle_syntax}
  ,
  {"MoveObject", N_("Select an Object"), ActionMoveObject,
   moveobject_help, moveobject_syntax}
  ,
  {"MoveToCurrentLayer", 0, ActionMoveToCurrentLayer,
   movetocurrentlayer_help, movetocurrentlayer_syntax}
  ,
  {"New", 0, ActionNew,
   new_help, new_syntax}
  ,
  {"pscalib", 0, ActionPSCalib}
  ,
  {"ElementList", 0, ActionElementList,
   elementlist_help, elementlist_syntax}
  ,
  {"ElementSetAttr", 0, ActionElementSetAttr,
   elementsetattr_help, elementsetattr_syntax}
  ,
  {"ExecCommand", 0, ActionExecCommand,
   execcommand_help, execcommand_syntax}
  ,
  {"ImportTinyCAD", 0, ActionImportTinyCAD,
   tcad_import_help, tcad_import_syntax}
  ,
  {"Import", 0, ActionImport,
   import_help, import_syntax}
  ,
  {"SetViaLayers", 0, ActionSetViaLayers,
   setvialayers_help, setvialayers_syntax}
  ,
};

REGISTER_ACTIONS (action_action_list)

