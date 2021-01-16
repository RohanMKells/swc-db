/**
 * Autogenerated by Thrift Compiler (0.13.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
package org.swcdb.thrift.gen;

@SuppressWarnings({"cast", "rawtypes", "serial", "unchecked", "unused"})
/**
 * The Key Cells for results on Key of scan
 */
public class kCells implements org.apache.thrift.TBase<kCells, kCells._Fields>, java.io.Serializable, Cloneable, Comparable<kCells> {
  private static final org.apache.thrift.protocol.TStruct STRUCT_DESC = new org.apache.thrift.protocol.TStruct("kCells");

  private static final org.apache.thrift.protocol.TField K_FIELD_DESC = new org.apache.thrift.protocol.TField("k", org.apache.thrift.protocol.TType.LIST, (short)1);
  private static final org.apache.thrift.protocol.TField CELLS_FIELD_DESC = new org.apache.thrift.protocol.TField("cells", org.apache.thrift.protocol.TType.LIST, (short)2);

  private static final org.apache.thrift.scheme.SchemeFactory STANDARD_SCHEME_FACTORY = new kCellsStandardSchemeFactory();
  private static final org.apache.thrift.scheme.SchemeFactory TUPLE_SCHEME_FACTORY = new kCellsTupleSchemeFactory();

  /**
   * The Cell Key
   */
  public @org.apache.thrift.annotation.Nullable java.util.List<java.nio.ByteBuffer> k; // required
  /**
   * The Key's Cells, defined as KCell items in a list-container
   */
  public @org.apache.thrift.annotation.Nullable java.util.List<KCell> cells; // required

  /** The set of fields this struct contains, along with convenience methods for finding and manipulating them. */
  public enum _Fields implements org.apache.thrift.TFieldIdEnum {
    /**
     * The Cell Key
     */
    K((short)1, "k"),
    /**
     * The Key's Cells, defined as KCell items in a list-container
     */
    CELLS((short)2, "cells");

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
        case 1: // K
          return K;
        case 2: // CELLS
          return CELLS;
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

    public short getThriftFieldId() {
      return _thriftId;
    }

    public java.lang.String getFieldName() {
      return _fieldName;
    }
  }

  // isset id assignments
  public static final java.util.Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> metaDataMap;
  static {
    java.util.Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> tmpMap = new java.util.EnumMap<_Fields, org.apache.thrift.meta_data.FieldMetaData>(_Fields.class);
    tmpMap.put(_Fields.K, new org.apache.thrift.meta_data.FieldMetaData("k", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.LIST        , "Key")));
    tmpMap.put(_Fields.CELLS, new org.apache.thrift.meta_data.FieldMetaData("cells", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.ListMetaData(org.apache.thrift.protocol.TType.LIST, 
            new org.apache.thrift.meta_data.StructMetaData(org.apache.thrift.protocol.TType.STRUCT, KCell.class))));
    metaDataMap = java.util.Collections.unmodifiableMap(tmpMap);
    org.apache.thrift.meta_data.FieldMetaData.addStructMetaDataMap(kCells.class, metaDataMap);
  }

  public kCells() {
  }

  public kCells(
    java.util.List<java.nio.ByteBuffer> k,
    java.util.List<KCell> cells)
  {
    this();
    this.k = k;
    this.cells = cells;
  }

  /**
   * Performs a deep copy on <i>other</i>.
   */
  public kCells(kCells other) {
    if (other.isSetK()) {
      java.util.List<java.nio.ByteBuffer> __this__k = new java.util.ArrayList<java.nio.ByteBuffer>(other.k);
      this.k = __this__k;
    }
    if (other.isSetCells()) {
      java.util.List<KCell> __this__cells = new java.util.ArrayList<KCell>(other.cells.size());
      for (KCell other_element : other.cells) {
        __this__cells.add(new KCell(other_element));
      }
      this.cells = __this__cells;
    }
  }

  public kCells deepCopy() {
    return new kCells(this);
  }

  @Override
  public void clear() {
    this.k = null;
    this.cells = null;
  }

  public int getKSize() {
    return (this.k == null) ? 0 : this.k.size();
  }

  @org.apache.thrift.annotation.Nullable
  public java.util.Iterator<java.nio.ByteBuffer> getKIterator() {
    return (this.k == null) ? null : this.k.iterator();
  }

  public void addToK(java.nio.ByteBuffer elem) {
    if (this.k == null) {
      this.k = new java.util.ArrayList<java.nio.ByteBuffer>();
    }
    this.k.add(elem);
  }

  /**
   * The Cell Key
   */
  @org.apache.thrift.annotation.Nullable
  public java.util.List<java.nio.ByteBuffer> getK() {
    return this.k;
  }

  /**
   * The Cell Key
   */
  public kCells setK(@org.apache.thrift.annotation.Nullable java.util.List<java.nio.ByteBuffer> k) {
    this.k = k;
    return this;
  }

  public void unsetK() {
    this.k = null;
  }

  /** Returns true if field k is set (has been assigned a value) and false otherwise */
  public boolean isSetK() {
    return this.k != null;
  }

  public void setKIsSet(boolean value) {
    if (!value) {
      this.k = null;
    }
  }

  public int getCellsSize() {
    return (this.cells == null) ? 0 : this.cells.size();
  }

  @org.apache.thrift.annotation.Nullable
  public java.util.Iterator<KCell> getCellsIterator() {
    return (this.cells == null) ? null : this.cells.iterator();
  }

  public void addToCells(KCell elem) {
    if (this.cells == null) {
      this.cells = new java.util.ArrayList<KCell>();
    }
    this.cells.add(elem);
  }

  /**
   * The Key's Cells, defined as KCell items in a list-container
   */
  @org.apache.thrift.annotation.Nullable
  public java.util.List<KCell> getCells() {
    return this.cells;
  }

  /**
   * The Key's Cells, defined as KCell items in a list-container
   */
  public kCells setCells(@org.apache.thrift.annotation.Nullable java.util.List<KCell> cells) {
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

  public void setFieldValue(_Fields field, @org.apache.thrift.annotation.Nullable java.lang.Object value) {
    switch (field) {
    case K:
      if (value == null) {
        unsetK();
      } else {
        setK((java.util.List<java.nio.ByteBuffer>)value);
      }
      break;

    case CELLS:
      if (value == null) {
        unsetCells();
      } else {
        setCells((java.util.List<KCell>)value);
      }
      break;

    }
  }

  @org.apache.thrift.annotation.Nullable
  public java.lang.Object getFieldValue(_Fields field) {
    switch (field) {
    case K:
      return getK();

    case CELLS:
      return getCells();

    }
    throw new java.lang.IllegalStateException();
  }

  /** Returns true if field corresponding to fieldID is set (has been assigned a value) and false otherwise */
  public boolean isSet(_Fields field) {
    if (field == null) {
      throw new java.lang.IllegalArgumentException();
    }

    switch (field) {
    case K:
      return isSetK();
    case CELLS:
      return isSetCells();
    }
    throw new java.lang.IllegalStateException();
  }

  @Override
  public boolean equals(java.lang.Object that) {
    if (that == null)
      return false;
    if (that instanceof kCells)
      return this.equals((kCells)that);
    return false;
  }

  public boolean equals(kCells that) {
    if (that == null)
      return false;
    if (this == that)
      return true;

    boolean this_present_k = true && this.isSetK();
    boolean that_present_k = true && that.isSetK();
    if (this_present_k || that_present_k) {
      if (!(this_present_k && that_present_k))
        return false;
      if (!this.k.equals(that.k))
        return false;
    }

    boolean this_present_cells = true && this.isSetCells();
    boolean that_present_cells = true && that.isSetCells();
    if (this_present_cells || that_present_cells) {
      if (!(this_present_cells && that_present_cells))
        return false;
      if (!this.cells.equals(that.cells))
        return false;
    }

    return true;
  }

  @Override
  public int hashCode() {
    int hashCode = 1;

    hashCode = hashCode * 8191 + ((isSetK()) ? 131071 : 524287);
    if (isSetK())
      hashCode = hashCode * 8191 + k.hashCode();

    hashCode = hashCode * 8191 + ((isSetCells()) ? 131071 : 524287);
    if (isSetCells())
      hashCode = hashCode * 8191 + cells.hashCode();

    return hashCode;
  }

  @Override
  public int compareTo(kCells other) {
    if (!getClass().equals(other.getClass())) {
      return getClass().getName().compareTo(other.getClass().getName());
    }

    int lastComparison = 0;

    lastComparison = java.lang.Boolean.valueOf(isSetK()).compareTo(other.isSetK());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetK()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.k, other.k);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = java.lang.Boolean.valueOf(isSetCells()).compareTo(other.isSetCells());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetCells()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.cells, other.cells);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    return 0;
  }

  @org.apache.thrift.annotation.Nullable
  public _Fields fieldForId(int fieldId) {
    return _Fields.findByThriftId(fieldId);
  }

  public void read(org.apache.thrift.protocol.TProtocol iprot) throws org.apache.thrift.TException {
    scheme(iprot).read(iprot, this);
  }

  public void write(org.apache.thrift.protocol.TProtocol oprot) throws org.apache.thrift.TException {
    scheme(oprot).write(oprot, this);
  }

  @Override
  public java.lang.String toString() {
    java.lang.StringBuilder sb = new java.lang.StringBuilder("kCells(");
    boolean first = true;

    sb.append("k:");
    if (this.k == null) {
      sb.append("null");
    } else {
      sb.append(this.k);
    }
    first = false;
    if (!first) sb.append(", ");
    sb.append("cells:");
    if (this.cells == null) {
      sb.append("null");
    } else {
      sb.append(this.cells);
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

  private static class kCellsStandardSchemeFactory implements org.apache.thrift.scheme.SchemeFactory {
    public kCellsStandardScheme getScheme() {
      return new kCellsStandardScheme();
    }
  }

  private static class kCellsStandardScheme extends org.apache.thrift.scheme.StandardScheme<kCells> {

    public void read(org.apache.thrift.protocol.TProtocol iprot, kCells struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TField schemeField;
      iprot.readStructBegin();
      while (true)
      {
        schemeField = iprot.readFieldBegin();
        if (schemeField.type == org.apache.thrift.protocol.TType.STOP) { 
          break;
        }
        switch (schemeField.id) {
          case 1: // K
            if (schemeField.type == org.apache.thrift.protocol.TType.LIST) {
              {
                org.apache.thrift.protocol.TList _list128 = iprot.readListBegin();
                struct.k = new java.util.ArrayList<java.nio.ByteBuffer>(_list128.size);
                @org.apache.thrift.annotation.Nullable java.nio.ByteBuffer _elem129;
                for (int _i130 = 0; _i130 < _list128.size; ++_i130)
                {
                  _elem129 = iprot.readBinary();
                  struct.k.add(_elem129);
                }
                iprot.readListEnd();
              }
              struct.setKIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 2: // CELLS
            if (schemeField.type == org.apache.thrift.protocol.TType.LIST) {
              {
                org.apache.thrift.protocol.TList _list131 = iprot.readListBegin();
                struct.cells = new java.util.ArrayList<KCell>(_list131.size);
                @org.apache.thrift.annotation.Nullable KCell _elem132;
                for (int _i133 = 0; _i133 < _list131.size; ++_i133)
                {
                  _elem132 = new KCell();
                  _elem132.read(iprot);
                  struct.cells.add(_elem132);
                }
                iprot.readListEnd();
              }
              struct.setCellsIsSet(true);
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

    public void write(org.apache.thrift.protocol.TProtocol oprot, kCells struct) throws org.apache.thrift.TException {
      struct.validate();

      oprot.writeStructBegin(STRUCT_DESC);
      if (struct.k != null) {
        oprot.writeFieldBegin(K_FIELD_DESC);
        {
          oprot.writeListBegin(new org.apache.thrift.protocol.TList(org.apache.thrift.protocol.TType.STRING, struct.k.size()));
          for (java.nio.ByteBuffer _iter134 : struct.k)
          {
            oprot.writeBinary(_iter134);
          }
          oprot.writeListEnd();
        }
        oprot.writeFieldEnd();
      }
      if (struct.cells != null) {
        oprot.writeFieldBegin(CELLS_FIELD_DESC);
        {
          oprot.writeListBegin(new org.apache.thrift.protocol.TList(org.apache.thrift.protocol.TType.STRUCT, struct.cells.size()));
          for (KCell _iter135 : struct.cells)
          {
            _iter135.write(oprot);
          }
          oprot.writeListEnd();
        }
        oprot.writeFieldEnd();
      }
      oprot.writeFieldStop();
      oprot.writeStructEnd();
    }

  }

  private static class kCellsTupleSchemeFactory implements org.apache.thrift.scheme.SchemeFactory {
    public kCellsTupleScheme getScheme() {
      return new kCellsTupleScheme();
    }
  }

  private static class kCellsTupleScheme extends org.apache.thrift.scheme.TupleScheme<kCells> {

    @Override
    public void write(org.apache.thrift.protocol.TProtocol prot, kCells struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TTupleProtocol oprot = (org.apache.thrift.protocol.TTupleProtocol) prot;
      java.util.BitSet optionals = new java.util.BitSet();
      if (struct.isSetK()) {
        optionals.set(0);
      }
      if (struct.isSetCells()) {
        optionals.set(1);
      }
      oprot.writeBitSet(optionals, 2);
      if (struct.isSetK()) {
        {
          oprot.writeI32(struct.k.size());
          for (java.nio.ByteBuffer _iter136 : struct.k)
          {
            oprot.writeBinary(_iter136);
          }
        }
      }
      if (struct.isSetCells()) {
        {
          oprot.writeI32(struct.cells.size());
          for (KCell _iter137 : struct.cells)
          {
            _iter137.write(oprot);
          }
        }
      }
    }

    @Override
    public void read(org.apache.thrift.protocol.TProtocol prot, kCells struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TTupleProtocol iprot = (org.apache.thrift.protocol.TTupleProtocol) prot;
      java.util.BitSet incoming = iprot.readBitSet(2);
      if (incoming.get(0)) {
        {
          org.apache.thrift.protocol.TList _list138 = new org.apache.thrift.protocol.TList(org.apache.thrift.protocol.TType.STRING, iprot.readI32());
          struct.k = new java.util.ArrayList<java.nio.ByteBuffer>(_list138.size);
          @org.apache.thrift.annotation.Nullable java.nio.ByteBuffer _elem139;
          for (int _i140 = 0; _i140 < _list138.size; ++_i140)
          {
            _elem139 = iprot.readBinary();
            struct.k.add(_elem139);
          }
        }
        struct.setKIsSet(true);
      }
      if (incoming.get(1)) {
        {
          org.apache.thrift.protocol.TList _list141 = new org.apache.thrift.protocol.TList(org.apache.thrift.protocol.TType.STRUCT, iprot.readI32());
          struct.cells = new java.util.ArrayList<KCell>(_list141.size);
          @org.apache.thrift.annotation.Nullable KCell _elem142;
          for (int _i143 = 0; _i143 < _list141.size; ++_i143)
          {
            _elem142 = new KCell();
            _elem142.read(iprot);
            struct.cells.add(_elem142);
          }
        }
        struct.setCellsIsSet(true);
      }
    }
  }

  private static <S extends org.apache.thrift.scheme.IScheme> S scheme(org.apache.thrift.protocol.TProtocol proto) {
    return (org.apache.thrift.scheme.StandardScheme.class.equals(proto.getScheme()) ? STANDARD_SCHEME_FACTORY : TUPLE_SCHEME_FACTORY).getScheme();
  }
}

