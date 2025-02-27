/**
 * Autogenerated by Thrift Compiler (0.17.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
package org.swcdb.thrift.gen;

/**
 * Serial LIST_BYTES Field Update
 */
@SuppressWarnings({"cast", "rawtypes", "serial", "unchecked", "unused"})
public class FU_LB implements org.apache.thrift.TBase<FU_LB, FU_LB._Fields>, java.io.Serializable, Cloneable, Comparable<FU_LB> {
  private static final org.apache.thrift.protocol.TStruct STRUCT_DESC = new org.apache.thrift.protocol.TStruct("FU_LB");

  private static final org.apache.thrift.protocol.TField CTRL_FIELD_DESC = new org.apache.thrift.protocol.TField("ctrl", org.apache.thrift.protocol.TType.BYTE, (short)1);
  private static final org.apache.thrift.protocol.TField OP_FIELD_DESC = new org.apache.thrift.protocol.TField("op", org.apache.thrift.protocol.TType.I32, (short)2);
  private static final org.apache.thrift.protocol.TField POS_FIELD_DESC = new org.apache.thrift.protocol.TField("pos", org.apache.thrift.protocol.TType.I32, (short)3);
  private static final org.apache.thrift.protocol.TField V_FIELD_DESC = new org.apache.thrift.protocol.TField("v", org.apache.thrift.protocol.TType.LIST, (short)4);

  private static final org.apache.thrift.scheme.SchemeFactory STANDARD_SCHEME_FACTORY = new FU_LBStandardSchemeFactory();
  private static final org.apache.thrift.scheme.SchemeFactory TUPLE_SCHEME_FACTORY = new FU_LBTupleSchemeFactory();

  public byte ctrl; // required
  /**
   * 
   * @see FU_LIST_OP
   */
  public @org.apache.thrift.annotation.Nullable FU_LIST_OP op; // required
  public int pos; // optional
  public @org.apache.thrift.annotation.Nullable java.util.List<FU_BYTES> v; // required

  /** The set of fields this struct contains, along with convenience methods for finding and manipulating them. */
  public enum _Fields implements org.apache.thrift.TFieldIdEnum {
    CTRL((short)1, "ctrl"),
    /**
     * 
     * @see FU_LIST_OP
     */
    OP((short)2, "op"),
    POS((short)3, "pos"),
    V((short)4, "v");

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
        case 1: // CTRL
          return CTRL;
        case 2: // OP
          return OP;
        case 3: // POS
          return POS;
        case 4: // V
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
  private static final int __CTRL_ISSET_ID = 0;
  private static final int __POS_ISSET_ID = 1;
  private byte __isset_bitfield = 0;
  private static final _Fields optionals[] = {_Fields.POS};
  public static final java.util.Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> metaDataMap;
  static {
    java.util.Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> tmpMap = new java.util.EnumMap<_Fields, org.apache.thrift.meta_data.FieldMetaData>(_Fields.class);
    tmpMap.put(_Fields.CTRL, new org.apache.thrift.meta_data.FieldMetaData("ctrl", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.BYTE)));
    tmpMap.put(_Fields.OP, new org.apache.thrift.meta_data.FieldMetaData("op", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.EnumMetaData(org.apache.thrift.protocol.TType.ENUM, FU_LIST_OP.class)));
    tmpMap.put(_Fields.POS, new org.apache.thrift.meta_data.FieldMetaData("pos", org.apache.thrift.TFieldRequirementType.OPTIONAL, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.I32)));
    tmpMap.put(_Fields.V, new org.apache.thrift.meta_data.FieldMetaData("v", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.ListMetaData(org.apache.thrift.protocol.TType.LIST, 
            new org.apache.thrift.meta_data.StructMetaData(org.apache.thrift.protocol.TType.STRUCT, FU_BYTES.class))));
    metaDataMap = java.util.Collections.unmodifiableMap(tmpMap);
    org.apache.thrift.meta_data.FieldMetaData.addStructMetaDataMap(FU_LB.class, metaDataMap);
  }

  public FU_LB() {
    this.ctrl = (byte)0;

    this.op = org.swcdb.thrift.gen.FU_LIST_OP.REPLACE;

  }

  public FU_LB(
    byte ctrl,
    FU_LIST_OP op,
    java.util.List<FU_BYTES> v)
  {
    this();
    this.ctrl = ctrl;
    setCtrlIsSet(true);
    this.op = op;
    this.v = v;
  }

  /**
   * Performs a deep copy on <i>other</i>.
   */
  public FU_LB(FU_LB other) {
    __isset_bitfield = other.__isset_bitfield;
    this.ctrl = other.ctrl;
    if (other.isSetOp()) {
      this.op = other.op;
    }
    this.pos = other.pos;
    if (other.isSetV()) {
      java.util.List<FU_BYTES> __this__v = new java.util.ArrayList<FU_BYTES>(other.v.size());
      for (FU_BYTES other_element : other.v) {
        __this__v.add(new FU_BYTES(other_element));
      }
      this.v = __this__v;
    }
  }

  @Override
  public FU_LB deepCopy() {
    return new FU_LB(this);
  }

  @Override
  public void clear() {
    this.ctrl = (byte)0;

    this.op = org.swcdb.thrift.gen.FU_LIST_OP.REPLACE;

    setPosIsSet(false);
    this.pos = 0;
    this.v = null;
  }

  public byte getCtrl() {
    return this.ctrl;
  }

  public FU_LB setCtrl(byte ctrl) {
    this.ctrl = ctrl;
    setCtrlIsSet(true);
    return this;
  }

  public void unsetCtrl() {
    __isset_bitfield = org.apache.thrift.EncodingUtils.clearBit(__isset_bitfield, __CTRL_ISSET_ID);
  }

  /** Returns true if field ctrl is set (has been assigned a value) and false otherwise */
  public boolean isSetCtrl() {
    return org.apache.thrift.EncodingUtils.testBit(__isset_bitfield, __CTRL_ISSET_ID);
  }

  public void setCtrlIsSet(boolean value) {
    __isset_bitfield = org.apache.thrift.EncodingUtils.setBit(__isset_bitfield, __CTRL_ISSET_ID, value);
  }

  /**
   * 
   * @see FU_LIST_OP
   */
  @org.apache.thrift.annotation.Nullable
  public FU_LIST_OP getOp() {
    return this.op;
  }

  /**
   * 
   * @see FU_LIST_OP
   */
  public FU_LB setOp(@org.apache.thrift.annotation.Nullable FU_LIST_OP op) {
    this.op = op;
    return this;
  }

  public void unsetOp() {
    this.op = null;
  }

  /** Returns true if field op is set (has been assigned a value) and false otherwise */
  public boolean isSetOp() {
    return this.op != null;
  }

  public void setOpIsSet(boolean value) {
    if (!value) {
      this.op = null;
    }
  }

  public int getPos() {
    return this.pos;
  }

  public FU_LB setPos(int pos) {
    this.pos = pos;
    setPosIsSet(true);
    return this;
  }

  public void unsetPos() {
    __isset_bitfield = org.apache.thrift.EncodingUtils.clearBit(__isset_bitfield, __POS_ISSET_ID);
  }

  /** Returns true if field pos is set (has been assigned a value) and false otherwise */
  public boolean isSetPos() {
    return org.apache.thrift.EncodingUtils.testBit(__isset_bitfield, __POS_ISSET_ID);
  }

  public void setPosIsSet(boolean value) {
    __isset_bitfield = org.apache.thrift.EncodingUtils.setBit(__isset_bitfield, __POS_ISSET_ID, value);
  }

  public int getVSize() {
    return (this.v == null) ? 0 : this.v.size();
  }

  @org.apache.thrift.annotation.Nullable
  public java.util.Iterator<FU_BYTES> getVIterator() {
    return (this.v == null) ? null : this.v.iterator();
  }

  public void addToV(FU_BYTES elem) {
    if (this.v == null) {
      this.v = new java.util.ArrayList<FU_BYTES>();
    }
    this.v.add(elem);
  }

  @org.apache.thrift.annotation.Nullable
  public java.util.List<FU_BYTES> getV() {
    return this.v;
  }

  public FU_LB setV(@org.apache.thrift.annotation.Nullable java.util.List<FU_BYTES> v) {
    this.v = v;
    return this;
  }

  public void unsetV() {
    this.v = null;
  }

  /** Returns true if field v is set (has been assigned a value) and false otherwise */
  public boolean isSetV() {
    return this.v != null;
  }

  public void setVIsSet(boolean value) {
    if (!value) {
      this.v = null;
    }
  }

  @Override
  public void setFieldValue(_Fields field, @org.apache.thrift.annotation.Nullable java.lang.Object value) {
    switch (field) {
    case CTRL:
      if (value == null) {
        unsetCtrl();
      } else {
        setCtrl((java.lang.Byte)value);
      }
      break;

    case OP:
      if (value == null) {
        unsetOp();
      } else {
        setOp((FU_LIST_OP)value);
      }
      break;

    case POS:
      if (value == null) {
        unsetPos();
      } else {
        setPos((java.lang.Integer)value);
      }
      break;

    case V:
      if (value == null) {
        unsetV();
      } else {
        setV((java.util.List<FU_BYTES>)value);
      }
      break;

    }
  }

  @org.apache.thrift.annotation.Nullable
  @Override
  public java.lang.Object getFieldValue(_Fields field) {
    switch (field) {
    case CTRL:
      return getCtrl();

    case OP:
      return getOp();

    case POS:
      return getPos();

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
    case CTRL:
      return isSetCtrl();
    case OP:
      return isSetOp();
    case POS:
      return isSetPos();
    case V:
      return isSetV();
    }
    throw new java.lang.IllegalStateException();
  }

  @Override
  public boolean equals(java.lang.Object that) {
    if (that instanceof FU_LB)
      return this.equals((FU_LB)that);
    return false;
  }

  public boolean equals(FU_LB that) {
    if (that == null)
      return false;
    if (this == that)
      return true;

    boolean this_present_ctrl = true;
    boolean that_present_ctrl = true;
    if (this_present_ctrl || that_present_ctrl) {
      if (!(this_present_ctrl && that_present_ctrl))
        return false;
      if (this.ctrl != that.ctrl)
        return false;
    }

    boolean this_present_op = true && this.isSetOp();
    boolean that_present_op = true && that.isSetOp();
    if (this_present_op || that_present_op) {
      if (!(this_present_op && that_present_op))
        return false;
      if (!this.op.equals(that.op))
        return false;
    }

    boolean this_present_pos = true && this.isSetPos();
    boolean that_present_pos = true && that.isSetPos();
    if (this_present_pos || that_present_pos) {
      if (!(this_present_pos && that_present_pos))
        return false;
      if (this.pos != that.pos)
        return false;
    }

    boolean this_present_v = true && this.isSetV();
    boolean that_present_v = true && that.isSetV();
    if (this_present_v || that_present_v) {
      if (!(this_present_v && that_present_v))
        return false;
      if (!this.v.equals(that.v))
        return false;
    }

    return true;
  }

  @Override
  public int hashCode() {
    int hashCode = 1;

    hashCode = hashCode * 8191 + (int) (ctrl);

    hashCode = hashCode * 8191 + ((isSetOp()) ? 131071 : 524287);
    if (isSetOp())
      hashCode = hashCode * 8191 + op.getValue();

    hashCode = hashCode * 8191 + ((isSetPos()) ? 131071 : 524287);
    if (isSetPos())
      hashCode = hashCode * 8191 + pos;

    hashCode = hashCode * 8191 + ((isSetV()) ? 131071 : 524287);
    if (isSetV())
      hashCode = hashCode * 8191 + v.hashCode();

    return hashCode;
  }

  @Override
  public int compareTo(FU_LB other) {
    if (!getClass().equals(other.getClass())) {
      return getClass().getName().compareTo(other.getClass().getName());
    }

    int lastComparison = 0;

    lastComparison = java.lang.Boolean.compare(isSetCtrl(), other.isSetCtrl());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetCtrl()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.ctrl, other.ctrl);
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
    lastComparison = java.lang.Boolean.compare(isSetPos(), other.isSetPos());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetPos()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.pos, other.pos);
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
    java.lang.StringBuilder sb = new java.lang.StringBuilder("FU_LB(");
    boolean first = true;

    sb.append("ctrl:");
    sb.append(this.ctrl);
    first = false;
    if (!first) sb.append(", ");
    sb.append("op:");
    if (this.op == null) {
      sb.append("null");
    } else {
      sb.append(this.op);
    }
    first = false;
    if (isSetPos()) {
      if (!first) sb.append(", ");
      sb.append("pos:");
      sb.append(this.pos);
      first = false;
    }
    if (!first) sb.append(", ");
    sb.append("v:");
    if (this.v == null) {
      sb.append("null");
    } else {
      sb.append(this.v);
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
      // it doesn't seem like you should have to do this, but java serialization is wacky, and doesn't call the default constructor.
      __isset_bitfield = 0;
      read(new org.apache.thrift.protocol.TCompactProtocol(new org.apache.thrift.transport.TIOStreamTransport(in)));
    } catch (org.apache.thrift.TException te) {
      throw new java.io.IOException(te);
    }
  }

  private static class FU_LBStandardSchemeFactory implements org.apache.thrift.scheme.SchemeFactory {
    @Override
    public FU_LBStandardScheme getScheme() {
      return new FU_LBStandardScheme();
    }
  }

  private static class FU_LBStandardScheme extends org.apache.thrift.scheme.StandardScheme<FU_LB> {

    @Override
    public void read(org.apache.thrift.protocol.TProtocol iprot, FU_LB struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TField schemeField;
      iprot.readStructBegin();
      while (true)
      {
        schemeField = iprot.readFieldBegin();
        if (schemeField.type == org.apache.thrift.protocol.TType.STOP) { 
          break;
        }
        switch (schemeField.id) {
          case 1: // CTRL
            if (schemeField.type == org.apache.thrift.protocol.TType.BYTE) {
              struct.ctrl = iprot.readByte();
              struct.setCtrlIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 2: // OP
            if (schemeField.type == org.apache.thrift.protocol.TType.I32) {
              struct.op = org.swcdb.thrift.gen.FU_LIST_OP.findByValue(iprot.readI32());
              struct.setOpIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 3: // POS
            if (schemeField.type == org.apache.thrift.protocol.TType.I32) {
              struct.pos = iprot.readI32();
              struct.setPosIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 4: // V
            if (schemeField.type == org.apache.thrift.protocol.TType.LIST) {
              {
                org.apache.thrift.protocol.TList _list320 = iprot.readListBegin();
                struct.v = new java.util.ArrayList<FU_BYTES>(_list320.size);
                @org.apache.thrift.annotation.Nullable FU_BYTES _elem321;
                for (int _i322 = 0; _i322 < _list320.size; ++_i322)
                {
                  _elem321 = new FU_BYTES();
                  _elem321.read(iprot);
                  struct.v.add(_elem321);
                }
                iprot.readListEnd();
              }
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
    public void write(org.apache.thrift.protocol.TProtocol oprot, FU_LB struct) throws org.apache.thrift.TException {
      struct.validate();

      oprot.writeStructBegin(STRUCT_DESC);
      oprot.writeFieldBegin(CTRL_FIELD_DESC);
      oprot.writeByte(struct.ctrl);
      oprot.writeFieldEnd();
      if (struct.op != null) {
        oprot.writeFieldBegin(OP_FIELD_DESC);
        oprot.writeI32(struct.op.getValue());
        oprot.writeFieldEnd();
      }
      if (struct.isSetPos()) {
        oprot.writeFieldBegin(POS_FIELD_DESC);
        oprot.writeI32(struct.pos);
        oprot.writeFieldEnd();
      }
      if (struct.v != null) {
        oprot.writeFieldBegin(V_FIELD_DESC);
        {
          oprot.writeListBegin(new org.apache.thrift.protocol.TList(org.apache.thrift.protocol.TType.STRUCT, struct.v.size()));
          for (FU_BYTES _iter323 : struct.v)
          {
            _iter323.write(oprot);
          }
          oprot.writeListEnd();
        }
        oprot.writeFieldEnd();
      }
      oprot.writeFieldStop();
      oprot.writeStructEnd();
    }

  }

  private static class FU_LBTupleSchemeFactory implements org.apache.thrift.scheme.SchemeFactory {
    @Override
    public FU_LBTupleScheme getScheme() {
      return new FU_LBTupleScheme();
    }
  }

  private static class FU_LBTupleScheme extends org.apache.thrift.scheme.TupleScheme<FU_LB> {

    @Override
    public void write(org.apache.thrift.protocol.TProtocol prot, FU_LB struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TTupleProtocol oprot = (org.apache.thrift.protocol.TTupleProtocol) prot;
      java.util.BitSet optionals = new java.util.BitSet();
      if (struct.isSetCtrl()) {
        optionals.set(0);
      }
      if (struct.isSetOp()) {
        optionals.set(1);
      }
      if (struct.isSetPos()) {
        optionals.set(2);
      }
      if (struct.isSetV()) {
        optionals.set(3);
      }
      oprot.writeBitSet(optionals, 4);
      if (struct.isSetCtrl()) {
        oprot.writeByte(struct.ctrl);
      }
      if (struct.isSetOp()) {
        oprot.writeI32(struct.op.getValue());
      }
      if (struct.isSetPos()) {
        oprot.writeI32(struct.pos);
      }
      if (struct.isSetV()) {
        {
          oprot.writeI32(struct.v.size());
          for (FU_BYTES _iter324 : struct.v)
          {
            _iter324.write(oprot);
          }
        }
      }
    }

    @Override
    public void read(org.apache.thrift.protocol.TProtocol prot, FU_LB struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TTupleProtocol iprot = (org.apache.thrift.protocol.TTupleProtocol) prot;
      java.util.BitSet incoming = iprot.readBitSet(4);
      if (incoming.get(0)) {
        struct.ctrl = iprot.readByte();
        struct.setCtrlIsSet(true);
      }
      if (incoming.get(1)) {
        struct.op = org.swcdb.thrift.gen.FU_LIST_OP.findByValue(iprot.readI32());
        struct.setOpIsSet(true);
      }
      if (incoming.get(2)) {
        struct.pos = iprot.readI32();
        struct.setPosIsSet(true);
      }
      if (incoming.get(3)) {
        {
          org.apache.thrift.protocol.TList _list325 = iprot.readListBegin(org.apache.thrift.protocol.TType.STRUCT);
          struct.v = new java.util.ArrayList<FU_BYTES>(_list325.size);
          @org.apache.thrift.annotation.Nullable FU_BYTES _elem326;
          for (int _i327 = 0; _i327 < _list325.size; ++_i327)
          {
            _elem326 = new FU_BYTES();
            _elem326.read(iprot);
            struct.v.add(_elem326);
          }
        }
        struct.setVIsSet(true);
      }
    }
  }

  private static <S extends org.apache.thrift.scheme.IScheme> S scheme(org.apache.thrift.protocol.TProtocol proto) {
    return (org.apache.thrift.scheme.StandardScheme.class.equals(proto.getScheme()) ? STANDARD_SCHEME_FACTORY : TUPLE_SCHEME_FACTORY).getScheme();
  }
}

