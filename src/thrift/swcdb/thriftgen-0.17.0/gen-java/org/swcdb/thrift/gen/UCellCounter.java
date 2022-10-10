/**
 * Autogenerated by Thrift Compiler (0.17.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
package org.swcdb.thrift.gen;

/**
 * The Cell data for using with Update of COUNTER Column Type
 */
@SuppressWarnings({"cast", "rawtypes", "serial", "unchecked", "unused"})
public class UCellCounter implements org.apache.thrift.TBase<UCellCounter, UCellCounter._Fields>, java.io.Serializable, Cloneable, Comparable<UCellCounter> {
  private static final org.apache.thrift.protocol.TStruct STRUCT_DESC = new org.apache.thrift.protocol.TStruct("UCellCounter");

  private static final org.apache.thrift.protocol.TField F_FIELD_DESC = new org.apache.thrift.protocol.TField("f", org.apache.thrift.protocol.TType.I32, (short)1);
  private static final org.apache.thrift.protocol.TField K_FIELD_DESC = new org.apache.thrift.protocol.TField("k", org.apache.thrift.protocol.TType.LIST, (short)2);
  private static final org.apache.thrift.protocol.TField TS_FIELD_DESC = new org.apache.thrift.protocol.TField("ts", org.apache.thrift.protocol.TType.I64, (short)3);
  private static final org.apache.thrift.protocol.TField TS_DESC_FIELD_DESC = new org.apache.thrift.protocol.TField("ts_desc", org.apache.thrift.protocol.TType.BOOL, (short)4);
  private static final org.apache.thrift.protocol.TField OP_FIELD_DESC = new org.apache.thrift.protocol.TField("op", org.apache.thrift.protocol.TType.BYTE, (short)5);
  private static final org.apache.thrift.protocol.TField V_FIELD_DESC = new org.apache.thrift.protocol.TField("v", org.apache.thrift.protocol.TType.I64, (short)6);

  private static final org.apache.thrift.scheme.SchemeFactory STANDARD_SCHEME_FACTORY = new UCellCounterStandardSchemeFactory();
  private static final org.apache.thrift.scheme.SchemeFactory TUPLE_SCHEME_FACTORY = new UCellCounterTupleSchemeFactory();

  /**
   * The Cell Flag
   * 
   * @see Flag
   */
  public @org.apache.thrift.annotation.Nullable Flag f; // required
  /**
   * The Cell Key
   */
  public @org.apache.thrift.annotation.Nullable java.util.List<java.nio.ByteBuffer> k; // required
  /**
   * The Cell Timestamp in nanoseconds
   */
  public long ts; // optional
  /**
   * The Cell Version is in timestamp descending
   */
  public boolean ts_desc; // optional
  /**
   * The Cell Counter Operation
   */
  public byte op; // required
  /**
   * The Cell Counter Value
   */
  public long v; // required

  /** The set of fields this struct contains, along with convenience methods for finding and manipulating them. */
  public enum _Fields implements org.apache.thrift.TFieldIdEnum {
    /**
     * The Cell Flag
     * 
     * @see Flag
     */
    F((short)1, "f"),
    /**
     * The Cell Key
     */
    K((short)2, "k"),
    /**
     * The Cell Timestamp in nanoseconds
     */
    TS((short)3, "ts"),
    /**
     * The Cell Version is in timestamp descending
     */
    TS_DESC((short)4, "ts_desc"),
    /**
     * The Cell Counter Operation
     */
    OP((short)5, "op"),
    /**
     * The Cell Counter Value
     */
    V((short)6, "v");

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
        case 1: // F
          return F;
        case 2: // K
          return K;
        case 3: // TS
          return TS;
        case 4: // TS_DESC
          return TS_DESC;
        case 5: // OP
          return OP;
        case 6: // V
          return V;
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
  private static final int __TS_ISSET_ID = 0;
  private static final int __TS_DESC_ISSET_ID = 1;
  private static final int __OP_ISSET_ID = 2;
  private static final int __V_ISSET_ID = 3;
  private byte __isset_bitfield = 0;
  private static final _Fields optionals[] = {_Fields.TS,_Fields.TS_DESC};
  public static final java.util.Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> metaDataMap;
  static {
    java.util.Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> tmpMap = new java.util.EnumMap<_Fields, org.apache.thrift.meta_data.FieldMetaData>(_Fields.class);
    tmpMap.put(_Fields.F, new org.apache.thrift.meta_data.FieldMetaData("f", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.EnumMetaData(org.apache.thrift.protocol.TType.ENUM, Flag.class)));
    tmpMap.put(_Fields.K, new org.apache.thrift.meta_data.FieldMetaData("k", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.LIST        , "Key")));
    tmpMap.put(_Fields.TS, new org.apache.thrift.meta_data.FieldMetaData("ts", org.apache.thrift.TFieldRequirementType.OPTIONAL, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.I64)));
    tmpMap.put(_Fields.TS_DESC, new org.apache.thrift.meta_data.FieldMetaData("ts_desc", org.apache.thrift.TFieldRequirementType.OPTIONAL, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.BOOL)));
    tmpMap.put(_Fields.OP, new org.apache.thrift.meta_data.FieldMetaData("op", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.BYTE)));
    tmpMap.put(_Fields.V, new org.apache.thrift.meta_data.FieldMetaData("v", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.I64)));
    metaDataMap = java.util.Collections.unmodifiableMap(tmpMap);
    org.apache.thrift.meta_data.FieldMetaData.addStructMetaDataMap(UCellCounter.class, metaDataMap);
  }

  public UCellCounter() {
    this.op = (byte)0;

    this.v = 0L;

  }

  public UCellCounter(
    Flag f,
    java.util.List<java.nio.ByteBuffer> k,
    byte op,
    long v)
  {
    this();
    this.f = f;
    this.k = k;
    this.op = op;
    setOpIsSet(true);
    this.v = v;
    setVIsSet(true);
  }

  /**
   * Performs a deep copy on <i>other</i>.
   */
  public UCellCounter(UCellCounter other) {
    __isset_bitfield = other.__isset_bitfield;
    if (other.isSetF()) {
      this.f = other.f;
    }
    if (other.isSetK()) {
      java.util.List<java.nio.ByteBuffer> __this__k = new java.util.ArrayList<java.nio.ByteBuffer>(other.k);
      this.k = __this__k;
    }
    this.ts = other.ts;
    this.ts_desc = other.ts_desc;
    this.op = other.op;
    this.v = other.v;
  }

  @Override
  public UCellCounter deepCopy() {
    return new UCellCounter(this);
  }

  @Override
  public void clear() {
    this.f = null;
    this.k = null;
    setTsIsSet(false);
    this.ts = 0;
    setTs_descIsSet(false);
    this.ts_desc = false;
    this.op = (byte)0;

    this.v = 0L;

  }

  /**
   * The Cell Flag
   * 
   * @see Flag
   */
  @org.apache.thrift.annotation.Nullable
  public Flag getF() {
    return this.f;
  }

  /**
   * The Cell Flag
   * 
   * @see Flag
   */
  public UCellCounter setF(@org.apache.thrift.annotation.Nullable Flag f) {
    this.f = f;
    return this;
  }

  public void unsetF() {
    this.f = null;
  }

  /** Returns true if field f is set (has been assigned a value) and false otherwise */
  public boolean isSetF() {
    return this.f != null;
  }

  public void setFIsSet(boolean value) {
    if (!value) {
      this.f = null;
    }
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
  public UCellCounter setK(@org.apache.thrift.annotation.Nullable java.util.List<java.nio.ByteBuffer> k) {
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

  /**
   * The Cell Timestamp in nanoseconds
   */
  public long getTs() {
    return this.ts;
  }

  /**
   * The Cell Timestamp in nanoseconds
   */
  public UCellCounter setTs(long ts) {
    this.ts = ts;
    setTsIsSet(true);
    return this;
  }

  public void unsetTs() {
    __isset_bitfield = org.apache.thrift.EncodingUtils.clearBit(__isset_bitfield, __TS_ISSET_ID);
  }

  /** Returns true if field ts is set (has been assigned a value) and false otherwise */
  public boolean isSetTs() {
    return org.apache.thrift.EncodingUtils.testBit(__isset_bitfield, __TS_ISSET_ID);
  }

  public void setTsIsSet(boolean value) {
    __isset_bitfield = org.apache.thrift.EncodingUtils.setBit(__isset_bitfield, __TS_ISSET_ID, value);
  }

  /**
   * The Cell Version is in timestamp descending
   */
  public boolean isTs_desc() {
    return this.ts_desc;
  }

  /**
   * The Cell Version is in timestamp descending
   */
  public UCellCounter setTs_desc(boolean ts_desc) {
    this.ts_desc = ts_desc;
    setTs_descIsSet(true);
    return this;
  }

  public void unsetTs_desc() {
    __isset_bitfield = org.apache.thrift.EncodingUtils.clearBit(__isset_bitfield, __TS_DESC_ISSET_ID);
  }

  /** Returns true if field ts_desc is set (has been assigned a value) and false otherwise */
  public boolean isSetTs_desc() {
    return org.apache.thrift.EncodingUtils.testBit(__isset_bitfield, __TS_DESC_ISSET_ID);
  }

  public void setTs_descIsSet(boolean value) {
    __isset_bitfield = org.apache.thrift.EncodingUtils.setBit(__isset_bitfield, __TS_DESC_ISSET_ID, value);
  }

  /**
   * The Cell Counter Operation
   */
  public byte getOp() {
    return this.op;
  }

  /**
   * The Cell Counter Operation
   */
  public UCellCounter setOp(byte op) {
    this.op = op;
    setOpIsSet(true);
    return this;
  }

  public void unsetOp() {
    __isset_bitfield = org.apache.thrift.EncodingUtils.clearBit(__isset_bitfield, __OP_ISSET_ID);
  }

  /** Returns true if field op is set (has been assigned a value) and false otherwise */
  public boolean isSetOp() {
    return org.apache.thrift.EncodingUtils.testBit(__isset_bitfield, __OP_ISSET_ID);
  }

  public void setOpIsSet(boolean value) {
    __isset_bitfield = org.apache.thrift.EncodingUtils.setBit(__isset_bitfield, __OP_ISSET_ID, value);
  }

  /**
   * The Cell Counter Value
   */
  public long getV() {
    return this.v;
  }

  /**
   * The Cell Counter Value
   */
  public UCellCounter setV(long v) {
    this.v = v;
    setVIsSet(true);
    return this;
  }

  public void unsetV() {
    __isset_bitfield = org.apache.thrift.EncodingUtils.clearBit(__isset_bitfield, __V_ISSET_ID);
  }

  /** Returns true if field v is set (has been assigned a value) and false otherwise */
  public boolean isSetV() {
    return org.apache.thrift.EncodingUtils.testBit(__isset_bitfield, __V_ISSET_ID);
  }

  public void setVIsSet(boolean value) {
    __isset_bitfield = org.apache.thrift.EncodingUtils.setBit(__isset_bitfield, __V_ISSET_ID, value);
  }

  @Override
  public void setFieldValue(_Fields field, @org.apache.thrift.annotation.Nullable java.lang.Object value) {
    switch (field) {
    case F:
      if (value == null) {
        unsetF();
      } else {
        setF((Flag)value);
      }
      break;

    case K:
      if (value == null) {
        unsetK();
      } else {
        setK((java.util.List<java.nio.ByteBuffer>)value);
      }
      break;

    case TS:
      if (value == null) {
        unsetTs();
      } else {
        setTs((java.lang.Long)value);
      }
      break;

    case TS_DESC:
      if (value == null) {
        unsetTs_desc();
      } else {
        setTs_desc((java.lang.Boolean)value);
      }
      break;

    case OP:
      if (value == null) {
        unsetOp();
      } else {
        setOp((java.lang.Byte)value);
      }
      break;

    case V:
      if (value == null) {
        unsetV();
      } else {
        setV((java.lang.Long)value);
      }
      break;

    }
  }

  @org.apache.thrift.annotation.Nullable
  @Override
  public java.lang.Object getFieldValue(_Fields field) {
    switch (field) {
    case F:
      return getF();

    case K:
      return getK();

    case TS:
      return getTs();

    case TS_DESC:
      return isTs_desc();

    case OP:
      return getOp();

    case V:
      return getV();

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
    case F:
      return isSetF();
    case K:
      return isSetK();
    case TS:
      return isSetTs();
    case TS_DESC:
      return isSetTs_desc();
    case OP:
      return isSetOp();
    case V:
      return isSetV();
    }
    throw new java.lang.IllegalStateException();
  }

  @Override
  public boolean equals(java.lang.Object that) {
    if (that instanceof UCellCounter)
      return this.equals((UCellCounter)that);
    return false;
  }

  public boolean equals(UCellCounter that) {
    if (that == null)
      return false;
    if (this == that)
      return true;

    boolean this_present_f = true && this.isSetF();
    boolean that_present_f = true && that.isSetF();
    if (this_present_f || that_present_f) {
      if (!(this_present_f && that_present_f))
        return false;
      if (!this.f.equals(that.f))
        return false;
    }

    boolean this_present_k = true && this.isSetK();
    boolean that_present_k = true && that.isSetK();
    if (this_present_k || that_present_k) {
      if (!(this_present_k && that_present_k))
        return false;
      if (!this.k.equals(that.k))
        return false;
    }

    boolean this_present_ts = true && this.isSetTs();
    boolean that_present_ts = true && that.isSetTs();
    if (this_present_ts || that_present_ts) {
      if (!(this_present_ts && that_present_ts))
        return false;
      if (this.ts != that.ts)
        return false;
    }

    boolean this_present_ts_desc = true && this.isSetTs_desc();
    boolean that_present_ts_desc = true && that.isSetTs_desc();
    if (this_present_ts_desc || that_present_ts_desc) {
      if (!(this_present_ts_desc && that_present_ts_desc))
        return false;
      if (this.ts_desc != that.ts_desc)
        return false;
    }

    boolean this_present_op = true;
    boolean that_present_op = true;
    if (this_present_op || that_present_op) {
      if (!(this_present_op && that_present_op))
        return false;
      if (this.op != that.op)
        return false;
    }

    boolean this_present_v = true;
    boolean that_present_v = true;
    if (this_present_v || that_present_v) {
      if (!(this_present_v && that_present_v))
        return false;
      if (this.v != that.v)
        return false;
    }

    return true;
  }

  @Override
  public int hashCode() {
    int hashCode = 1;

    hashCode = hashCode * 8191 + ((isSetF()) ? 131071 : 524287);
    if (isSetF())
      hashCode = hashCode * 8191 + f.getValue();

    hashCode = hashCode * 8191 + ((isSetK()) ? 131071 : 524287);
    if (isSetK())
      hashCode = hashCode * 8191 + k.hashCode();

    hashCode = hashCode * 8191 + ((isSetTs()) ? 131071 : 524287);
    if (isSetTs())
      hashCode = hashCode * 8191 + org.apache.thrift.TBaseHelper.hashCode(ts);

    hashCode = hashCode * 8191 + ((isSetTs_desc()) ? 131071 : 524287);
    if (isSetTs_desc())
      hashCode = hashCode * 8191 + ((ts_desc) ? 131071 : 524287);

    hashCode = hashCode * 8191 + (int) (op);

    hashCode = hashCode * 8191 + org.apache.thrift.TBaseHelper.hashCode(v);

    return hashCode;
  }

  @Override
  public int compareTo(UCellCounter other) {
    if (!getClass().equals(other.getClass())) {
      return getClass().getName().compareTo(other.getClass().getName());
    }

    int lastComparison = 0;

    lastComparison = java.lang.Boolean.compare(isSetF(), other.isSetF());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetF()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.f, other.f);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = java.lang.Boolean.compare(isSetK(), other.isSetK());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetK()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.k, other.k);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = java.lang.Boolean.compare(isSetTs(), other.isSetTs());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetTs()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.ts, other.ts);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = java.lang.Boolean.compare(isSetTs_desc(), other.isSetTs_desc());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetTs_desc()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.ts_desc, other.ts_desc);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = java.lang.Boolean.compare(isSetOp(), other.isSetOp());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetOp()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.op, other.op);
      if (lastComparison != 0) {
        return lastComparison;
      }
    }
    lastComparison = java.lang.Boolean.compare(isSetV(), other.isSetV());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetV()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.v, other.v);
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
    java.lang.StringBuilder sb = new java.lang.StringBuilder("UCellCounter(");
    boolean first = true;

    sb.append("f:");
    if (this.f == null) {
      sb.append("null");
    } else {
      sb.append(this.f);
    }
    first = false;
    if (!first) sb.append(", ");
    sb.append("k:");
    if (this.k == null) {
      sb.append("null");
    } else {
      sb.append(this.k);
    }
    first = false;
    if (isSetTs()) {
      if (!first) sb.append(", ");
      sb.append("ts:");
      sb.append(this.ts);
      first = false;
    }
    if (isSetTs_desc()) {
      if (!first) sb.append(", ");
      sb.append("ts_desc:");
      sb.append(this.ts_desc);
      first = false;
    }
    if (!first) sb.append(", ");
    sb.append("op:");
    sb.append(this.op);
    first = false;
    if (!first) sb.append(", ");
    sb.append("v:");
    sb.append(this.v);
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
      // it doesn't seem like you should have to do this, but java serialization is wacky, and doesn't call the default constructor.
      __isset_bitfield = 0;
      read(new org.apache.thrift.protocol.TCompactProtocol(new org.apache.thrift.transport.TIOStreamTransport(in)));
    } catch (org.apache.thrift.TException te) {
      throw new java.io.IOException(te);
    }
  }

  private static class UCellCounterStandardSchemeFactory implements org.apache.thrift.scheme.SchemeFactory {
    @Override
    public UCellCounterStandardScheme getScheme() {
      return new UCellCounterStandardScheme();
    }
  }

  private static class UCellCounterStandardScheme extends org.apache.thrift.scheme.StandardScheme<UCellCounter> {

    @Override
    public void read(org.apache.thrift.protocol.TProtocol iprot, UCellCounter struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TField schemeField;
      iprot.readStructBegin();
      while (true)
      {
        schemeField = iprot.readFieldBegin();
        if (schemeField.type == org.apache.thrift.protocol.TType.STOP) { 
          break;
        }
        switch (schemeField.id) {
          case 1: // F
            if (schemeField.type == org.apache.thrift.protocol.TType.I32) {
              struct.f = org.swcdb.thrift.gen.Flag.findByValue(iprot.readI32());
              struct.setFIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 2: // K
            if (schemeField.type == org.apache.thrift.protocol.TType.LIST) {
              {
                org.apache.thrift.protocol.TList _list224 = iprot.readListBegin();
                struct.k = new java.util.ArrayList<java.nio.ByteBuffer>(_list224.size);
                @org.apache.thrift.annotation.Nullable java.nio.ByteBuffer _elem225;
                for (int _i226 = 0; _i226 < _list224.size; ++_i226)
                {
                  _elem225 = iprot.readBinary();
                  struct.k.add(_elem225);
                }
                iprot.readListEnd();
              }
              struct.setKIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 3: // TS
            if (schemeField.type == org.apache.thrift.protocol.TType.I64) {
              struct.ts = iprot.readI64();
              struct.setTsIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 4: // TS_DESC
            if (schemeField.type == org.apache.thrift.protocol.TType.BOOL) {
              struct.ts_desc = iprot.readBool();
              struct.setTs_descIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 5: // OP
            if (schemeField.type == org.apache.thrift.protocol.TType.BYTE) {
              struct.op = iprot.readByte();
              struct.setOpIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 6: // V
            if (schemeField.type == org.apache.thrift.protocol.TType.I64) {
              struct.v = iprot.readI64();
              struct.setVIsSet(true);
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
    public void write(org.apache.thrift.protocol.TProtocol oprot, UCellCounter struct) throws org.apache.thrift.TException {
      struct.validate();

      oprot.writeStructBegin(STRUCT_DESC);
      if (struct.f != null) {
        oprot.writeFieldBegin(F_FIELD_DESC);
        oprot.writeI32(struct.f.getValue());
        oprot.writeFieldEnd();
      }
      if (struct.k != null) {
        oprot.writeFieldBegin(K_FIELD_DESC);
        {
          oprot.writeListBegin(new org.apache.thrift.protocol.TList(org.apache.thrift.protocol.TType.STRING, struct.k.size()));
          for (java.nio.ByteBuffer _iter227 : struct.k)
          {
            oprot.writeBinary(_iter227);
          }
          oprot.writeListEnd();
        }
        oprot.writeFieldEnd();
      }
      if (struct.isSetTs()) {
        oprot.writeFieldBegin(TS_FIELD_DESC);
        oprot.writeI64(struct.ts);
        oprot.writeFieldEnd();
      }
      if (struct.isSetTs_desc()) {
        oprot.writeFieldBegin(TS_DESC_FIELD_DESC);
        oprot.writeBool(struct.ts_desc);
        oprot.writeFieldEnd();
      }
      oprot.writeFieldBegin(OP_FIELD_DESC);
      oprot.writeByte(struct.op);
      oprot.writeFieldEnd();
      oprot.writeFieldBegin(V_FIELD_DESC);
      oprot.writeI64(struct.v);
      oprot.writeFieldEnd();
      oprot.writeFieldStop();
      oprot.writeStructEnd();
    }

  }

  private static class UCellCounterTupleSchemeFactory implements org.apache.thrift.scheme.SchemeFactory {
    @Override
    public UCellCounterTupleScheme getScheme() {
      return new UCellCounterTupleScheme();
    }
  }

  private static class UCellCounterTupleScheme extends org.apache.thrift.scheme.TupleScheme<UCellCounter> {

    @Override
    public void write(org.apache.thrift.protocol.TProtocol prot, UCellCounter struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TTupleProtocol oprot = (org.apache.thrift.protocol.TTupleProtocol) prot;
      java.util.BitSet optionals = new java.util.BitSet();
      if (struct.isSetF()) {
        optionals.set(0);
      }
      if (struct.isSetK()) {
        optionals.set(1);
      }
      if (struct.isSetTs()) {
        optionals.set(2);
      }
      if (struct.isSetTs_desc()) {
        optionals.set(3);
      }
      if (struct.isSetOp()) {
        optionals.set(4);
      }
      if (struct.isSetV()) {
        optionals.set(5);
      }
      oprot.writeBitSet(optionals, 6);
      if (struct.isSetF()) {
        oprot.writeI32(struct.f.getValue());
      }
      if (struct.isSetK()) {
        {
          oprot.writeI32(struct.k.size());
          for (java.nio.ByteBuffer _iter228 : struct.k)
          {
            oprot.writeBinary(_iter228);
          }
        }
      }
      if (struct.isSetTs()) {
        oprot.writeI64(struct.ts);
      }
      if (struct.isSetTs_desc()) {
        oprot.writeBool(struct.ts_desc);
      }
      if (struct.isSetOp()) {
        oprot.writeByte(struct.op);
      }
      if (struct.isSetV()) {
        oprot.writeI64(struct.v);
      }
    }

    @Override
    public void read(org.apache.thrift.protocol.TProtocol prot, UCellCounter struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TTupleProtocol iprot = (org.apache.thrift.protocol.TTupleProtocol) prot;
      java.util.BitSet incoming = iprot.readBitSet(6);
      if (incoming.get(0)) {
        struct.f = org.swcdb.thrift.gen.Flag.findByValue(iprot.readI32());
        struct.setFIsSet(true);
      }
      if (incoming.get(1)) {
        {
          org.apache.thrift.protocol.TList _list229 = iprot.readListBegin(org.apache.thrift.protocol.TType.STRING);
          struct.k = new java.util.ArrayList<java.nio.ByteBuffer>(_list229.size);
          @org.apache.thrift.annotation.Nullable java.nio.ByteBuffer _elem230;
          for (int _i231 = 0; _i231 < _list229.size; ++_i231)
          {
            _elem230 = iprot.readBinary();
            struct.k.add(_elem230);
          }
        }
        struct.setKIsSet(true);
      }
      if (incoming.get(2)) {
        struct.ts = iprot.readI64();
        struct.setTsIsSet(true);
      }
      if (incoming.get(3)) {
        struct.ts_desc = iprot.readBool();
        struct.setTs_descIsSet(true);
      }
      if (incoming.get(4)) {
        struct.op = iprot.readByte();
        struct.setOpIsSet(true);
      }
      if (incoming.get(5)) {
        struct.v = iprot.readI64();
        struct.setVIsSet(true);
      }
    }
  }

  private static <S extends org.apache.thrift.scheme.IScheme> S scheme(org.apache.thrift.protocol.TProtocol proto) {
    return (org.apache.thrift.scheme.StandardScheme.class.equals(proto.getScheme()) ? STANDARD_SCHEME_FACTORY : TUPLE_SCHEME_FACTORY).getScheme();
  }
}

