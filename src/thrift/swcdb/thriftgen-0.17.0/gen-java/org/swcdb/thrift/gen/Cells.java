/**
 * Autogenerated by Thrift Compiler (0.17.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
package org.swcdb.thrift.gen;

/**
 * The Cells for results list of scan
 */
@SuppressWarnings({"cast", "rawtypes", "serial", "unchecked", "unused"})
public class Cells implements org.apache.thrift.TBase<Cells, Cells._Fields>, java.io.Serializable, Cloneable, Comparable<Cells> {
  private static final org.apache.thrift.protocol.TStruct STRUCT_DESC = new org.apache.thrift.protocol.TStruct("Cells");

  private static final org.apache.thrift.protocol.TField PLAIN_CELLS_FIELD_DESC = new org.apache.thrift.protocol.TField("plain_cells", org.apache.thrift.protocol.TType.LIST, (short)1);
  private static final org.apache.thrift.protocol.TField COUNTER_CELLS_FIELD_DESC = new org.apache.thrift.protocol.TField("counter_cells", org.apache.thrift.protocol.TType.LIST, (short)2);
  private static final org.apache.thrift.protocol.TField SERIAL_CELLS_FIELD_DESC = new org.apache.thrift.protocol.TField("serial_cells", org.apache.thrift.protocol.TType.LIST, (short)3);

  private static final org.apache.thrift.scheme.SchemeFactory STANDARD_SCHEME_FACTORY = new CellsStandardSchemeFactory();
  private static final org.apache.thrift.scheme.SchemeFactory TUPLE_SCHEME_FACTORY = new CellsTupleSchemeFactory();

  /**
   * The Cells, defined as Cell items in a list-container
   */
  public @org.apache.thrift.annotation.Nullable java.util.List<CellPlain> plain_cells; // required
  /**
   * The Cells, defined as Cell items in a list-container
   */
  public @org.apache.thrift.annotation.Nullable java.util.List<CellCounter> counter_cells; // required
  /**
   * The Serial Cells, defined as CellSerial items in a list-container
   */
  public @org.apache.thrift.annotation.Nullable java.util.List<CellSerial> serial_cells; // required

  /** The set of fields this struct contains, along with convenience methods for finding and manipulating them. */
  public enum _Fields implements org.apache.thrift.TFieldIdEnum {
    /**
     * The Cells, defined as Cell items in a list-container
     */
    PLAIN_CELLS((short)1, "plain_cells"),
    /**
     * The Cells, defined as Cell items in a list-container
     */
    COUNTER_CELLS((short)2, "counter_cells"),
    /**
     * The Serial Cells, defined as CellSerial items in a list-container
     */
    SERIAL_CELLS((short)3, "serial_cells");

    private static final java.util.Map<java.lang.String, _Fields> byName = new java.util.HashMap<java.lang.String, _Fields>();

    static {
      for (_Fields field : java.util.EnumSet.allOf(_Fields.class)) {
        byName.put(field.getFieldName(), field);
      }
    }

    /**
     * Find the _Fields constant that matches fieldId, or null if its not found.
     */
    @org.apache.thrift.annotation.Nullable
    public static _Fields findByThriftId(int fieldId) {
      switch(fieldId) {
        case 1: // PLAIN_CELLS
          return PLAIN_CELLS;
        case 2: // COUNTER_CELLS
          return COUNTER_CELLS;
        case 3: // SERIAL_CELLS
          return SERIAL_CELLS;
        default:
          return null;
      }
    }

    /**
     * Find the _Fields constant that matches fieldId, throwing an exception
     * if it is not found.
     */
    public static _Fields findByThriftIdOrThrow(int fieldId) {
      _Fields fields = findByThriftId(fieldId);
      if (fields == null) throw new java.lang.IllegalArgumentException("Field " + fieldId + " doesn't exist!");
      return fields;
    }

    /**
     * Find the _Fields constant that matches name, or null if its not found.
     */
    @org.apache.thrift.annotation.Nullable
    public static _Fields findByName(java.lang.String name) {
      return byName.get(name);
    }

    private final short _thriftId;
    private final java.lang.String _fieldName;

    _Fields(short thriftId, java.lang.String fieldName) {
      _thriftId = thriftId;
      _fieldName = fieldName;
    }

    @Override
    public short getThriftFieldId() {
      return _thriftId;
    }

    @Override
    public java.lang.String getFieldName() {
      return _fieldName;
    }
  }

  // isset id assignments
  public static final java.util.Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> metaDataMap;
  static {
    java.util.Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> tmpMap = new java.util.EnumMap<_Fields, org.apache.thrift.meta_data.FieldMetaData>(_Fields.class);
    tmpMap.put(_Fields.PLAIN_CELLS, new org.apache.thrift.meta_data.FieldMetaData("plain_cells", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.LIST        , "CellsPlain")));
    tmpMap.put(_Fields.COUNTER_CELLS, new org.apache.thrift.meta_data.FieldMetaData("counter_cells", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.LIST        , "CellsCounter")));
    tmpMap.put(_Fields.SERIAL_CELLS, new org.apache.thrift.meta_data.FieldMetaData("serial_cells", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.LIST        , "CellsSerial")));
    metaDataMap = java.util.Collections.unmodifiableMap(tmpMap);
    org.apache.thrift.meta_data.FieldMetaData.addStructMetaDataMap(Cells.class, metaDataMap);
  }

  public Cells() {
  }

  public Cells(
    java.util.List<CellPlain> plain_cells,
    java.util.List<CellCounter> counter_cells,
    java.util.List<CellSerial> serial_cells)
  {
    this();
    this.plain_cells = plain_cells;
    this.counter_cells = counter_cells;
    this.serial_cells = serial_cells;
  }

  /**
   * Performs a deep copy on <i>other</i>.
   */
  public Cells(Cells other) {
    if (other.isSetPlain_cells()) {
      java.util.List<CellPlain> __this__plain_cells = new java.util.ArrayList<CellPlain>(other.plain_cells.size());
      for (CellPlain other_element : other.plain_cells) {
        __this__plain_cells.add(new CellPlain(other_element));
      }
      this.plain_cells = __this__plain_cells;
    }
    if (other.isSetCounter_cells()) {
      java.util.List<CellCounter> __this__counter_cells = new java.util.ArrayList<CellCounter>(other.counter_cells.size());
      for (CellCounter other_element : other.counter_cells) {
        __this__counter_cells.add(new CellCounter(other_element));
      }
      this.counter_cells = __this__counter_cells;
    }
    if (other.isSetSerial_cells()) {
      java.util.List<CellSerial> __this__serial_cells = new java.util.ArrayList<CellSerial>(other.serial_cells.size());
      for (CellSerial other_element : other.serial_cells) {
        __this__serial_cells.add(new CellSerial(other_element));
      }
      this.serial_cells = __this__serial_cells;
    }
  }

  @Override
  public Cells deepCopy() {
    return new Cells(this);
  }

  @Override
  public void clear() {
    this.plain_cells = null;
    this.counter_cells = null;
    this.serial_cells = null;
  }

  public int getPlain_cellsSize() {
    return (this.plain_cells == null) ? 0 : this.plain_cells.size();
  }

  @org.apache.thrift.annotation.Nullable
  public java.util.Iterator<CellPlain> getPlain_cellsIterator() {
    return (this.plain_cells == null) ? null : this.plain_cells.iterator();
  }

  public void addToPlain_cells(CellPlain elem) {
    if (this.plain_cells == null) {
      this.plain_cells = new java.util.ArrayList<CellPlain>();
    }
    this.plain_cells.add(elem);
  }

  /**
   * The Cells, defined as Cell items in a list-container
   */
  @org.apache.thrift.annotation.Nullable
  public java.util.List<CellPlain> getPlain_cells() {
    return this.plain_cells;
  }

  /**
   * The Cells, defined as Cell items in a list-container
   */
  public Cells setPlain_cells(@org.apache.thrift.annotation.Nullable java.util.List<CellPlain> plain_cells) {
    this.plain_cells = plain_cells;
    return this;
  }

  public void unsetPlain_cells() {
    this.plain_cells = null;
  }

  /** Returns true if field plain_cells is set (has been assigned a value) and false otherwise */
  public boolean isSetPlain_cells() {
    return this.plain_cells != null;
  }

  public void setPlain_cellsIsSet(boolean value) {
    if (!value) {
      this.plain_cells = null;
    }
  }

  public int getCounter_cellsSize() {
    return (this.counter_cells == null) ? 0 : this.counter_cells.size();
  }

  @org.apache.thrift.annotation.Nullable
  public java.util.Iterator<CellCounter> getCounter_cellsIterator() {
    return (this.counter_cells == null) ? null : this.counter_cells.iterator();
  }

  public void addToCounter_cells(CellCounter elem) {
    if (this.counter_cells == null) {
      this.counter_cells = new java.util.ArrayList<CellCounter>();
    }
    this.counter_cells.add(elem);
  }

  /**
   * The Cells, defined as Cell items in a list-container
   */
  @org.apache.thrift.annotation.Nullable
  public java.util.List<CellCounter> getCounter_cells() {
    return this.counter_cells;
  }

  /**
   * The Cells, defined as Cell items in a list-container
   */
  public Cells setCounter_cells(@org.apache.thrift.annotation.Nullable java.util.List<CellCounter> counter_cells) {
    this.counter_cells = counter_cells;
    return this;
  }

  public void unsetCounter_cells() {
    this.counter_cells = null;
  }

  /** Returns true if field counter_cells is set (has been assigned a value) and false otherwise */
  public boolean isSetCounter_cells() {
    return this.counter_cells != null;
  }

  public void setCounter_cellsIsSet(boolean value) {
    if (!value) {
      this.counter_cells = null;
    }
  }

  public int getSerial_cellsSize() {
    return (this.serial_cells == null) ? 0 : this.serial_cells.size();
  }

  @org.apache.thrift.annotation.Nullable
  public java.util.Iterator<CellSerial> getSerial_cellsIterator() {
    return (this.serial_cells == null) ? null : this.serial_cells.iterator();
  }

  public void addToSerial_cells(CellSerial elem) {
    if (this.serial_cells == null) {
      this.serial_cells = new java.util.ArrayList<CellSerial>();
    }
    this.serial_cells.add(elem);
  }

  /**
   * The Serial Cells, defined as CellSerial items in a list-container
   */
  @org.apache.thrift.annotation.Nullable
  public java.util.List<CellSerial> getSerial_cells() {
    return this.serial_cells;
  }

  /**
   * The Serial Cells, defined as CellSerial items in a list-container
   */
  public Cells setSerial_cells(@org.apache.thrift.annotation.Nullable java.util.List<CellSerial> serial_cells) {
    this.serial_cells = serial_cells;
    return this;
  }

  public void unsetSerial_cells() {
    this.serial_cells = null;
  }

  /** Returns true if field serial_cells is set (has been assigned a value) and false otherwise */
  public boolean isSetSerial_cells() {
    return this.serial_cells != null;
  }

  public void setSerial_cellsIsSet(boolean value) {
    if (!value) {
      this.serial_cells = null;
    }
  }

  @Override
  public void setFieldValue(_Fields field, @org.apache.thrift.annotation.Nullable java.lang.Object value) {
    switch (field) {
    case PLAIN_CELLS:
      if (value == null) {
        unsetPlain_cells();
      } else {
        setPlain_cells((java.util.List<CellPlain>)value);
      }
      break;

    case COUNTER_CELLS:
      if (value == null) {
        unsetCounter_cells();
      } else {
        setCounter_cells((java.util.List<CellCounter>)value);
      }
      break;

    case SERIAL_CELLS:
      if (value == null) {
        unsetSerial_cells();
      } else {
        setSerial_cells((java.util.List<CellSerial>)value);
      }
      break;

    }
  }

  @org.apache.thrift.annotation.Nullable
  @Override
  public java.lang.Object getFieldValue(_Fields field) {
    switch (field) {
    case PLAIN_CELLS:
      return getPlain_cells();

    case COUNTER_CELLS:
      return getCounter_cells();

    case SERIAL_CELLS:
      return getSerial_cells();

    }
    throw new java.lang.IllegalStateException();
  }

  /** Returns true if field corresponding to fieldID is set (has been assigned a value) and false otherwise */
  @Override
  public boolean isSet(_Fields field) {
    if (field == null) {
      throw new java.lang.IllegalArgumentException();
    }

    switch (field) {
    case PLAIN_CELLS:
      return isSetPlain_cells();
    case COUNTER_CELLS:
      return isSetCounter_cells();
    case SERIAL_CELLS:
      return isSetSerial_cells();
    }
    throw new java.lang.IllegalStateException();
  }

  @Override
  public boolean equals(java.lang.Object that) {
    if (that instanceof Cells)
      return this.equals((Cells)that);
    return false;
  }

  public boolean equals(Cells that) {
    if (that == null)
      return false;
    if (this == that)
      return true;

    boolean this_present_plain_cells = true && this.isSetPlain_cells();
    boolean that_present_plain_cells = true && that.isSetPlain_cells();
    if (this_present_plain_cells || that_present_plain_cells) {
      if (!(this_present_plain_cells && that_present_plain_cells))
        return false;
      if (!this.plain_cells.equals(that.plain_cells))
        return false;
    }

    boolean this_present_counter_cells = true && this.isSetCounter_cells();
    boolean that_present_counter_cells = true && that.isSetCounter_cells();
    if (this_present_counter_cells || that_present_counter_cells) {
      if (!(this_present_counter_cells && that_present_counter_cells))
        return false;
      if (!this.counter_cells.equals(that.counter_cells))
        return false;
    }

    boolean this_present_serial_cells = true && this.isSetSerial_cells();
    boolean that_present_serial_cells = true && that.isSetSerial_cells();
    if (this_present_serial_cells || that_present_serial_cells) {
      if (!(this_present_serial_cells && that_present_serial_cells))
        return false;
      if (!this.serial_cells.equals(that.serial_cells))
        return false;
    }

    return true;
  }

  @Override
  public int hashCode() {
    int hashCode = 1;

    hashCode = hashCode * 8191 + ((isSetPlain_cells()) ? 131071 : 524287);
    if (isSetPlain_cells())
      hashCode = hashCode * 8191 + plain_cells.hashCode();

    hashCode = hashCode * 8191 + ((isSetCounter_cells()) ? 131071 : 524287);
    if (isSetCounter_cells())
      hashCode = hashCode * 8191 + counter_cells.hashCode();

    hashCode = hashCode * 8191 + ((isSetSerial_cells()) ? 131071 : 524287);
    if (isSetSerial_cells())
      hashCode = hashCode * 8191 + serial_cells.hashCode();

    return hashCode;
  }

  @Override
  public int compareTo(Cells other) {
    if (!getClass().equals(other.getClass())) {
      return getClass().getName().compareTo(other.getClass().getName());
    }

    int lastComparison = 0;

    lastComparison = java.lang.Boolean.compare(isSetPlain_cells(), other.isSetPlain_cells());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetPlain_cells()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.plain_cells, other.plain_cells);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = java.lang.Boolean.compare(isSetCounter_cells(), other.isSetCounter_cells());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetCounter_cells()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.counter_cells, other.counter_cells);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = java.lang.Boolean.compare(isSetSerial_cells(), other.isSetSerial_cells());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetSerial_cells()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.serial_cells, other.serial_cells);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    return 0;
  }

  @org.apache.thrift.annotation.Nullable
  @Override
  public _Fields fieldForId(int fieldId) {
    return _Fields.findByThriftId(fieldId);
  }

  @Override
  public void read(org.apache.thrift.protocol.TProtocol iprot) throws org.apache.thrift.TException {
    scheme(iprot).read(iprot, this);
  }

  @Override
  public void write(org.apache.thrift.protocol.TProtocol oprot) throws org.apache.thrift.TException {
    scheme(oprot).write(oprot, this);
  }

  @Override
  public java.lang.String toString() {
    java.lang.StringBuilder sb = new java.lang.StringBuilder("Cells(");
    boolean first = true;

    sb.append("plain_cells:");
    if (this.plain_cells == null) {
      sb.append("null");
    } else {
      sb.append(this.plain_cells);
    }
    first = false;
    if (!first) sb.append(", ");
    sb.append("counter_cells:");
    if (this.counter_cells == null) {
      sb.append("null");
    } else {
      sb.append(this.counter_cells);
    }
    first = false;
    if (!first) sb.append(", ");
    sb.append("serial_cells:");
    if (this.serial_cells == null) {
      sb.append("null");
    } else {
      sb.append(this.serial_cells);
    }
    first = false;
    sb.append(")");
    return sb.toString();
  }

  public void validate() throws org.apache.thrift.TException {
    // check for required fields
    // check for sub-struct validity
  }

  private void writeObject(java.io.ObjectOutputStream out) throws java.io.IOException {
    try {
      write(new org.apache.thrift.protocol.TCompactProtocol(new org.apache.thrift.transport.TIOStreamTransport(out)));
    } catch (org.apache.thrift.TException te) {
      throw new java.io.IOException(te);
    }
  }

  private void readObject(java.io.ObjectInputStream in) throws java.io.IOException, java.lang.ClassNotFoundException {
    try {
      read(new org.apache.thrift.protocol.TCompactProtocol(new org.apache.thrift.transport.TIOStreamTransport(in)));
    } catch (org.apache.thrift.TException te) {
      throw new java.io.IOException(te);
    }
  }

  private static class CellsStandardSchemeFactory implements org.apache.thrift.scheme.SchemeFactory {
    @Override
    public CellsStandardScheme getScheme() {
      return new CellsStandardScheme();
    }
  }

  private static class CellsStandardScheme extends org.apache.thrift.scheme.StandardScheme<Cells> {

    @Override
    public void read(org.apache.thrift.protocol.TProtocol iprot, Cells struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TField schemeField;
      iprot.readStructBegin();
      while (true)
      {
        schemeField = iprot.readFieldBegin();
        if (schemeField.type == org.apache.thrift.protocol.TType.STOP) { 
          break;
        }
        switch (schemeField.id) {
          case 1: // PLAIN_CELLS
            if (schemeField.type == org.apache.thrift.protocol.TType.LIST) {
              {
                org.apache.thrift.protocol.TList _list328 = iprot.readListBegin();
                struct.plain_cells = new java.util.ArrayList<CellPlain>(_list328.size);
                @org.apache.thrift.annotation.Nullable CellPlain _elem329;
                for (int _i330 = 0; _i330 < _list328.size; ++_i330)
                {
                  _elem329 = new CellPlain();
                  _elem329.read(iprot);
                  struct.plain_cells.add(_elem329);
                }
                iprot.readListEnd();
              }
              struct.setPlain_cellsIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 2: // COUNTER_CELLS
            if (schemeField.type == org.apache.thrift.protocol.TType.LIST) {
              {
                org.apache.thrift.protocol.TList _list331 = iprot.readListBegin();
                struct.counter_cells = new java.util.ArrayList<CellCounter>(_list331.size);
                @org.apache.thrift.annotation.Nullable CellCounter _elem332;
                for (int _i333 = 0; _i333 < _list331.size; ++_i333)
                {
                  _elem332 = new CellCounter();
                  _elem332.read(iprot);
                  struct.counter_cells.add(_elem332);
                }
                iprot.readListEnd();
              }
              struct.setCounter_cellsIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 3: // SERIAL_CELLS
            if (schemeField.type == org.apache.thrift.protocol.TType.LIST) {
              {
                org.apache.thrift.protocol.TList _list334 = iprot.readListBegin();
                struct.serial_cells = new java.util.ArrayList<CellSerial>(_list334.size);
                @org.apache.thrift.annotation.Nullable CellSerial _elem335;
                for (int _i336 = 0; _i336 < _list334.size; ++_i336)
                {
                  _elem335 = new CellSerial();
                  _elem335.read(iprot);
                  struct.serial_cells.add(_elem335);
                }
                iprot.readListEnd();
              }
              struct.setSerial_cellsIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          default:
            org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
        }
        iprot.readFieldEnd();
      }
      iprot.readStructEnd();

      // check for required fields of primitive type, which can't be checked in the validate method
      struct.validate();
    }

    @Override
    public void write(org.apache.thrift.protocol.TProtocol oprot, Cells struct) throws org.apache.thrift.TException {
      struct.validate();

      oprot.writeStructBegin(STRUCT_DESC);
      if (struct.plain_cells != null) {
        oprot.writeFieldBegin(PLAIN_CELLS_FIELD_DESC);
        {
          oprot.writeListBegin(new org.apache.thrift.protocol.TList(org.apache.thrift.protocol.TType.STRUCT, struct.plain_cells.size()));
          for (CellPlain _iter337 : struct.plain_cells)
          {
            _iter337.write(oprot);
          }
          oprot.writeListEnd();
        }
        oprot.writeFieldEnd();
      }
      if (struct.counter_cells != null) {
        oprot.writeFieldBegin(COUNTER_CELLS_FIELD_DESC);
        {
          oprot.writeListBegin(new org.apache.thrift.protocol.TList(org.apache.thrift.protocol.TType.STRUCT, struct.counter_cells.size()));
          for (CellCounter _iter338 : struct.counter_cells)
          {
            _iter338.write(oprot);
          }
          oprot.writeListEnd();
        }
        oprot.writeFieldEnd();
      }
      if (struct.serial_cells != null) {
        oprot.writeFieldBegin(SERIAL_CELLS_FIELD_DESC);
        {
          oprot.writeListBegin(new org.apache.thrift.protocol.TList(org.apache.thrift.protocol.TType.STRUCT, struct.serial_cells.size()));
          for (CellSerial _iter339 : struct.serial_cells)
          {
            _iter339.write(oprot);
          }
          oprot.writeListEnd();
        }
        oprot.writeFieldEnd();
      }
      oprot.writeFieldStop();
      oprot.writeStructEnd();
    }

  }

  private static class CellsTupleSchemeFactory implements org.apache.thrift.scheme.SchemeFactory {
    @Override
    public CellsTupleScheme getScheme() {
      return new CellsTupleScheme();
    }
  }

  private static class CellsTupleScheme extends org.apache.thrift.scheme.TupleScheme<Cells> {

    @Override
    public void write(org.apache.thrift.protocol.TProtocol prot, Cells struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TTupleProtocol oprot = (org.apache.thrift.protocol.TTupleProtocol) prot;
      java.util.BitSet optionals = new java.util.BitSet();
      if (struct.isSetPlain_cells()) {
        optionals.set(0);
      }
      if (struct.isSetCounter_cells()) {
        optionals.set(1);
      }
      if (struct.isSetSerial_cells()) {
        optionals.set(2);
      }
      oprot.writeBitSet(optionals, 3);
      if (struct.isSetPlain_cells()) {
        {
          oprot.writeI32(struct.plain_cells.size());
          for (CellPlain _iter340 : struct.plain_cells)
          {
            _iter340.write(oprot);
          }
        }
      }
      if (struct.isSetCounter_cells()) {
        {
          oprot.writeI32(struct.counter_cells.size());
          for (CellCounter _iter341 : struct.counter_cells)
          {
            _iter341.write(oprot);
          }
        }
      }
      if (struct.isSetSerial_cells()) {
        {
          oprot.writeI32(struct.serial_cells.size());
          for (CellSerial _iter342 : struct.serial_cells)
          {
            _iter342.write(oprot);
          }
        }
      }
    }

    @Override
    public void read(org.apache.thrift.protocol.TProtocol prot, Cells struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TTupleProtocol iprot = (org.apache.thrift.protocol.TTupleProtocol) prot;
      java.util.BitSet incoming = iprot.readBitSet(3);
      if (incoming.get(0)) {
        {
          org.apache.thrift.protocol.TList _list343 = iprot.readListBegin(org.apache.thrift.protocol.TType.STRUCT);
          struct.plain_cells = new java.util.ArrayList<CellPlain>(_list343.size);
          @org.apache.thrift.annotation.Nullable CellPlain _elem344;
          for (int _i345 = 0; _i345 < _list343.size; ++_i345)
          {
            _elem344 = new CellPlain();
            _elem344.read(iprot);
            struct.plain_cells.add(_elem344);
          }
        }
        struct.setPlain_cellsIsSet(true);
      }
      if (incoming.get(1)) {
        {
          org.apache.thrift.protocol.TList _list346 = iprot.readListBegin(org.apache.thrift.protocol.TType.STRUCT);
          struct.counter_cells = new java.util.ArrayList<CellCounter>(_list346.size);
          @org.apache.thrift.annotation.Nullable CellCounter _elem347;
          for (int _i348 = 0; _i348 < _list346.size; ++_i348)
          {
            _elem347 = new CellCounter();
            _elem347.read(iprot);
            struct.counter_cells.add(_elem347);
          }
        }
        struct.setCounter_cellsIsSet(true);
      }
      if (incoming.get(2)) {
        {
          org.apache.thrift.protocol.TList _list349 = iprot.readListBegin(org.apache.thrift.protocol.TType.STRUCT);
          struct.serial_cells = new java.util.ArrayList<CellSerial>(_list349.size);
          @org.apache.thrift.annotation.Nullable CellSerial _elem350;
          for (int _i351 = 0; _i351 < _list349.size; ++_i351)
          {
            _elem350 = new CellSerial();
            _elem350.read(iprot);
            struct.serial_cells.add(_elem350);
          }
        }
        struct.setSerial_cellsIsSet(true);
      }
    }
  }

  private static <S extends org.apache.thrift.scheme.IScheme> S scheme(org.apache.thrift.protocol.TProtocol proto) {
    return (org.apache.thrift.scheme.StandardScheme.class.equals(proto.getScheme()) ? STANDARD_SCHEME_FACTORY : TUPLE_SCHEME_FACTORY).getScheme();
  }
}

