/**
 * Autogenerated by Thrift Compiler (0.17.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
package org.swcdb.thrift.gen;

/**
 * The Column Cells for results on Columns of scan
 */
@SuppressWarnings({"cast", "rawtypes", "serial", "unchecked", "unused"})
public class ColCells implements org.apache.thrift.TBase<ColCells, ColCells._Fields>, java.io.Serializable, Cloneable, Comparable<ColCells> {
  private static final org.apache.thrift.protocol.TStruct STRUCT_DESC = new org.apache.thrift.protocol.TStruct("ColCells");

  private static final org.apache.thrift.protocol.TField CELLS_FIELD_DESC = new org.apache.thrift.protocol.TField("cells", org.apache.thrift.protocol.TType.LIST, (short)1);
  private static final org.apache.thrift.protocol.TField SERIAL_CELLS_FIELD_DESC = new org.apache.thrift.protocol.TField("serial_cells", org.apache.thrift.protocol.TType.LIST, (short)2);

  private static final org.apache.thrift.scheme.SchemeFactory STANDARD_SCHEME_FACTORY = new ColCellsStandardSchemeFactory();
  private static final org.apache.thrift.scheme.SchemeFactory TUPLE_SCHEME_FACTORY = new ColCellsTupleSchemeFactory();

  /**
   * The Cells, defined as CCell items in a list-container
   */
  public @org.apache.thrift.annotation.Nullable java.util.List<CCell> cells; // required
  /**
   * The Serial Cells, defined as CCellSerial items in a list-container
   */
  public @org.apache.thrift.annotation.Nullable java.util.List<CCellSerial> serial_cells; // required

  /** The set of fields this struct contains, along with convenience methods for finding and manipulating them. */
  public enum _Fields implements org.apache.thrift.TFieldIdEnum {
    /**
     * The Cells, defined as CCell items in a list-container
     */
    CELLS((short)1, "cells"),
    /**
     * The Serial Cells, defined as CCellSerial items in a list-container
     */
    SERIAL_CELLS((short)2, "serial_cells");

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
        case 1: // CELLS
          return CELLS;
        case 2: // SERIAL_CELLS
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
    tmpMap.put(_Fields.CELLS, new org.apache.thrift.meta_data.FieldMetaData("cells", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.ListMetaData(org.apache.thrift.protocol.TType.LIST, 
            new org.apache.thrift.meta_data.StructMetaData(org.apache.thrift.protocol.TType.STRUCT, CCell.class))));
    tmpMap.put(_Fields.SERIAL_CELLS, new org.apache.thrift.meta_data.FieldMetaData("serial_cells", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.ListMetaData(org.apache.thrift.protocol.TType.LIST, 
            new org.apache.thrift.meta_data.StructMetaData(org.apache.thrift.protocol.TType.STRUCT, CCellSerial.class))));
    metaDataMap = java.util.Collections.unmodifiableMap(tmpMap);
    org.apache.thrift.meta_data.FieldMetaData.addStructMetaDataMap(ColCells.class, metaDataMap);
  }

  public ColCells() {
  }

  public ColCells(
    java.util.List<CCell> cells,
    java.util.List<CCellSerial> serial_cells)
  {
    this();
    this.cells = cells;
    this.serial_cells = serial_cells;
  }

  /**
   * Performs a deep copy on <i>other</i>.
   */
  public ColCells(ColCells other) {
    if (other.isSetCells()) {
      java.util.List<CCell> __this__cells = new java.util.ArrayList<CCell>(other.cells.size());
      for (CCell other_element : other.cells) {
        __this__cells.add(new CCell(other_element));
      }
      this.cells = __this__cells;
    }
    if (other.isSetSerial_cells()) {
      java.util.List<CCellSerial> __this__serial_cells = new java.util.ArrayList<CCellSerial>(other.serial_cells.size());
      for (CCellSerial other_element : other.serial_cells) {
        __this__serial_cells.add(new CCellSerial(other_element));
      }
      this.serial_cells = __this__serial_cells;
    }
  }

  @Override
  public ColCells deepCopy() {
    return new ColCells(this);
  }

  @Override
  public void clear() {
    this.cells = null;
    this.serial_cells = null;
  }

  public int getCellsSize() {
    return (this.cells == null) ? 0 : this.cells.size();
  }

  @org.apache.thrift.annotation.Nullable
  public java.util.Iterator<CCell> getCellsIterator() {
    return (this.cells == null) ? null : this.cells.iterator();
  }

  public void addToCells(CCell elem) {
    if (this.cells == null) {
      this.cells = new java.util.ArrayList<CCell>();
    }
    this.cells.add(elem);
  }

  /**
   * The Cells, defined as CCell items in a list-container
   */
  @org.apache.thrift.annotation.Nullable
  public java.util.List<CCell> getCells() {
    return this.cells;
  }

  /**
   * The Cells, defined as CCell items in a list-container
   */
  public ColCells setCells(@org.apache.thrift.annotation.Nullable java.util.List<CCell> cells) {
    this.cells = cells;
    return this;
  }

  public void unsetCells() {
    this.cells = null;
  }

  /** Returns true if field cells is set (has been assigned a value) and false otherwise */
  public boolean isSetCells() {
    return this.cells != null;
  }

  public void setCellsIsSet(boolean value) {
    if (!value) {
      this.cells = null;
    }
  }

  public int getSerial_cellsSize() {
    return (this.serial_cells == null) ? 0 : this.serial_cells.size();
  }

  @org.apache.thrift.annotation.Nullable
  public java.util.Iterator<CCellSerial> getSerial_cellsIterator() {
    return (this.serial_cells == null) ? null : this.serial_cells.iterator();
  }

  public void addToSerial_cells(CCellSerial elem) {
    if (this.serial_cells == null) {
      this.serial_cells = new java.util.ArrayList<CCellSerial>();
    }
    this.serial_cells.add(elem);
  }

  /**
   * The Serial Cells, defined as CCellSerial items in a list-container
   */
  @org.apache.thrift.annotation.Nullable
  public java.util.List<CCellSerial> getSerial_cells() {
    return this.serial_cells;
  }

  /**
   * The Serial Cells, defined as CCellSerial items in a list-container
   */
  public ColCells setSerial_cells(@org.apache.thrift.annotation.Nullable java.util.List<CCellSerial> serial_cells) {
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
    case CELLS:
      if (value == null) {
        unsetCells();
      } else {
        setCells((java.util.List<CCell>)value);
      }
      break;

    case SERIAL_CELLS:
      if (value == null) {
        unsetSerial_cells();
      } else {
        setSerial_cells((java.util.List<CCellSerial>)value);
      }
      break;

    }
  }

  @org.apache.thrift.annotation.Nullable
  @Override
  public java.lang.Object getFieldValue(_Fields field) {
    switch (field) {
    case CELLS:
      return getCells();

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
    case CELLS:
      return isSetCells();
    case SERIAL_CELLS:
      return isSetSerial_cells();
    }
    throw new java.lang.IllegalStateException();
  }

  @Override
  public boolean equals(java.lang.Object that) {
    if (that instanceof ColCells)
      return this.equals((ColCells)that);
    return false;
  }

  public boolean equals(ColCells that) {
    if (that == null)
      return false;
    if (this == that)
      return true;

    boolean this_present_cells = true && this.isSetCells();
    boolean that_present_cells = true && that.isSetCells();
    if (this_present_cells || that_present_cells) {
      if (!(this_present_cells && that_present_cells))
        return false;
      if (!this.cells.equals(that.cells))
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

    hashCode = hashCode * 8191 + ((isSetCells()) ? 131071 : 524287);
    if (isSetCells())
      hashCode = hashCode * 8191 + cells.hashCode();

    hashCode = hashCode * 8191 + ((isSetSerial_cells()) ? 131071 : 524287);
    if (isSetSerial_cells())
      hashCode = hashCode * 8191 + serial_cells.hashCode();

    return hashCode;
  }

  @Override
  public int compareTo(ColCells other) {
    if (!getClass().equals(other.getClass())) {
      return getClass().getName().compareTo(other.getClass().getName());
    }

    int lastComparison = 0;

    lastComparison = java.lang.Boolean.compare(isSetCells(), other.isSetCells());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetCells()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.cells, other.cells);
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
    java.lang.StringBuilder sb = new java.lang.StringBuilder("ColCells(");
    boolean first = true;

    sb.append("cells:");
    if (this.cells == null) {
      sb.append("null");
    } else {
      sb.append(this.cells);
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

  private static class ColCellsStandardSchemeFactory implements org.apache.thrift.scheme.SchemeFactory {
    @Override
    public ColCellsStandardScheme getScheme() {
      return new ColCellsStandardScheme();
    }
  }

  private static class ColCellsStandardScheme extends org.apache.thrift.scheme.StandardScheme<ColCells> {

    @Override
    public void read(org.apache.thrift.protocol.TProtocol iprot, ColCells struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TField schemeField;
      iprot.readStructBegin();
      while (true)
      {
        schemeField = iprot.readFieldBegin();
        if (schemeField.type == org.apache.thrift.protocol.TType.STOP) { 
          break;
        }
        switch (schemeField.id) {
          case 1: // CELLS
            if (schemeField.type == org.apache.thrift.protocol.TType.LIST) {
              {
                org.apache.thrift.protocol.TList _list368 = iprot.readListBegin();
                struct.cells = new java.util.ArrayList<CCell>(_list368.size);
                @org.apache.thrift.annotation.Nullable CCell _elem369;
                for (int _i370 = 0; _i370 < _list368.size; ++_i370)
                {
                  _elem369 = new CCell();
                  _elem369.read(iprot);
                  struct.cells.add(_elem369);
                }
                iprot.readListEnd();
              }
              struct.setCellsIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 2: // SERIAL_CELLS
            if (schemeField.type == org.apache.thrift.protocol.TType.LIST) {
              {
                org.apache.thrift.protocol.TList _list371 = iprot.readListBegin();
                struct.serial_cells = new java.util.ArrayList<CCellSerial>(_list371.size);
                @org.apache.thrift.annotation.Nullable CCellSerial _elem372;
                for (int _i373 = 0; _i373 < _list371.size; ++_i373)
                {
                  _elem372 = new CCellSerial();
                  _elem372.read(iprot);
                  struct.serial_cells.add(_elem372);
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
    public void write(org.apache.thrift.protocol.TProtocol oprot, ColCells struct) throws org.apache.thrift.TException {
      struct.validate();

      oprot.writeStructBegin(STRUCT_DESC);
      if (struct.cells != null) {
        oprot.writeFieldBegin(CELLS_FIELD_DESC);
        {
          oprot.writeListBegin(new org.apache.thrift.protocol.TList(org.apache.thrift.protocol.TType.STRUCT, struct.cells.size()));
          for (CCell _iter374 : struct.cells)
          {
            _iter374.write(oprot);
          }
          oprot.writeListEnd();
        }
        oprot.writeFieldEnd();
      }
      if (struct.serial_cells != null) {
        oprot.writeFieldBegin(SERIAL_CELLS_FIELD_DESC);
        {
          oprot.writeListBegin(new org.apache.thrift.protocol.TList(org.apache.thrift.protocol.TType.STRUCT, struct.serial_cells.size()));
          for (CCellSerial _iter375 : struct.serial_cells)
          {
            _iter375.write(oprot);
          }
          oprot.writeListEnd();
        }
        oprot.writeFieldEnd();
      }
      oprot.writeFieldStop();
      oprot.writeStructEnd();
    }

  }

  private static class ColCellsTupleSchemeFactory implements org.apache.thrift.scheme.SchemeFactory {
    @Override
    public ColCellsTupleScheme getScheme() {
      return new ColCellsTupleScheme();
    }
  }

  private static class ColCellsTupleScheme extends org.apache.thrift.scheme.TupleScheme<ColCells> {

    @Override
    public void write(org.apache.thrift.protocol.TProtocol prot, ColCells struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TTupleProtocol oprot = (org.apache.thrift.protocol.TTupleProtocol) prot;
      java.util.BitSet optionals = new java.util.BitSet();
      if (struct.isSetCells()) {
        optionals.set(0);
      }
      if (struct.isSetSerial_cells()) {
        optionals.set(1);
      }
      oprot.writeBitSet(optionals, 2);
      if (struct.isSetCells()) {
        {
          oprot.writeI32(struct.cells.size());
          for (CCell _iter376 : struct.cells)
          {
            _iter376.write(oprot);
          }
        }
      }
      if (struct.isSetSerial_cells()) {
        {
          oprot.writeI32(struct.serial_cells.size());
          for (CCellSerial _iter377 : struct.serial_cells)
          {
            _iter377.write(oprot);
          }
        }
      }
    }

    @Override
    public void read(org.apache.thrift.protocol.TProtocol prot, ColCells struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TTupleProtocol iprot = (org.apache.thrift.protocol.TTupleProtocol) prot;
      java.util.BitSet incoming = iprot.readBitSet(2);
      if (incoming.get(0)) {
        {
          org.apache.thrift.protocol.TList _list378 = iprot.readListBegin(org.apache.thrift.protocol.TType.STRUCT);
          struct.cells = new java.util.ArrayList<CCell>(_list378.size);
          @org.apache.thrift.annotation.Nullable CCell _elem379;
          for (int _i380 = 0; _i380 < _list378.size; ++_i380)
          {
            _elem379 = new CCell();
            _elem379.read(iprot);
            struct.cells.add(_elem379);
          }
        }
        struct.setCellsIsSet(true);
      }
      if (incoming.get(1)) {
        {
          org.apache.thrift.protocol.TList _list381 = iprot.readListBegin(org.apache.thrift.protocol.TType.STRUCT);
          struct.serial_cells = new java.util.ArrayList<CCellSerial>(_list381.size);
          @org.apache.thrift.annotation.Nullable CCellSerial _elem382;
          for (int _i383 = 0; _i383 < _list381.size; ++_i383)
          {
            _elem382 = new CCellSerial();
            _elem382.read(iprot);
            struct.serial_cells.add(_elem382);
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

