/**
 * Autogenerated by Thrift Compiler (0.17.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
package org.swcdb.thrift.gen;

/**
 * The Counter Value Specifications, option to use with Extended Logical Comparators
 */
@SuppressWarnings({"cast", "rawtypes", "serial", "unchecked", "unused"})
public class SpecValueCounter implements org.apache.thrift.TBase<SpecValueCounter, SpecValueCounter._Fields>, java.io.Serializable, Cloneable, Comparable<SpecValueCounter> {
  private static final org.apache.thrift.protocol.TStruct STRUCT_DESC = new org.apache.thrift.protocol.TStruct("SpecValueCounter");

  private static final org.apache.thrift.protocol.TField COMP_FIELD_DESC = new org.apache.thrift.protocol.TField("comp", org.apache.thrift.protocol.TType.I32, (short)1);
  private static final org.apache.thrift.protocol.TField V_FIELD_DESC = new org.apache.thrift.protocol.TField("v", org.apache.thrift.protocol.TType.I64, (short)2);

  private static final org.apache.thrift.scheme.SchemeFactory STANDARD_SCHEME_FACTORY = new SpecValueCounterStandardSchemeFactory();
  private static final org.apache.thrift.scheme.SchemeFactory TUPLE_SCHEME_FACTORY = new SpecValueCounterTupleSchemeFactory();

  /**
   * Logical comparator to Apply
   * 
   * @see Comp
   */
  public @org.apache.thrift.annotation.Nullable Comp comp; // required
  /**
   * The int64 to match against the Cell value
   */
  public long v; // required

  /** The set of fields this struct contains, along with convenience methods for finding and manipulating them. */
  public enum _Fields implements org.apache.thrift.TFieldIdEnum {
    /**
     * Logical comparator to Apply
     * 
     * @see Comp
     */
    COMP((short)1, "comp"),
    /**
     * The int64 to match against the Cell value
     */
    V((short)2, "v");

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
        case 1: // COMP
          return COMP;
        case 2: // V
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
  private static final int __V_ISSET_ID = 0;
  private byte __isset_bitfield = 0;
  public static final java.util.Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> metaDataMap;
  static {
    java.util.Map<_Fields, org.apache.thrift.meta_data.FieldMetaData> tmpMap = new java.util.EnumMap<_Fields, org.apache.thrift.meta_data.FieldMetaData>(_Fields.class);
    tmpMap.put(_Fields.COMP, new org.apache.thrift.meta_data.FieldMetaData("comp", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.EnumMetaData(org.apache.thrift.protocol.TType.ENUM, Comp.class)));
    tmpMap.put(_Fields.V, new org.apache.thrift.meta_data.FieldMetaData("v", org.apache.thrift.TFieldRequirementType.DEFAULT, 
        new org.apache.thrift.meta_data.FieldValueMetaData(org.apache.thrift.protocol.TType.I64)));
    metaDataMap = java.util.Collections.unmodifiableMap(tmpMap);
    org.apache.thrift.meta_data.FieldMetaData.addStructMetaDataMap(SpecValueCounter.class, metaDataMap);
  }

  public SpecValueCounter() {
  }

  public SpecValueCounter(
    Comp comp,
    long v)
  {
    this();
    this.comp = comp;
    this.v = v;
    setVIsSet(true);
  }

  /**
   * Performs a deep copy on <i>other</i>.
   */
  public SpecValueCounter(SpecValueCounter other) {
    __isset_bitfield = other.__isset_bitfield;
    if (other.isSetComp()) {
      this.comp = other.comp;
    }
    this.v = other.v;
  }

  @Override
  public SpecValueCounter deepCopy() {
    return new SpecValueCounter(this);
  }

  @Override
  public void clear() {
    this.comp = null;
    setVIsSet(false);
    this.v = 0;
  }

  /**
   * Logical comparator to Apply
   * 
   * @see Comp
   */
  @org.apache.thrift.annotation.Nullable
  public Comp getComp() {
    return this.comp;
  }

  /**
   * Logical comparator to Apply
   * 
   * @see Comp
   */
  public SpecValueCounter setComp(@org.apache.thrift.annotation.Nullable Comp comp) {
    this.comp = comp;
    return this;
  }

  public void unsetComp() {
    this.comp = null;
  }

  /** Returns true if field comp is set (has been assigned a value) and false otherwise */
  public boolean isSetComp() {
    return this.comp != null;
  }

  public void setCompIsSet(boolean value) {
    if (!value) {
      this.comp = null;
    }
  }

  /**
   * The int64 to match against the Cell value
   */
  public long getV() {
    return this.v;
  }

  /**
   * The int64 to match against the Cell value
   */
  public SpecValueCounter setV(long v) {
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
    case COMP:
      if (value == null) {
        unsetComp();
      } else {
        setComp((Comp)value);
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
    case COMP:
      return getComp();

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
    case COMP:
      return isSetComp();
    case V:
      return isSetV();
    }
    throw new java.lang.IllegalStateException();
  }

  @Override
  public boolean equals(java.lang.Object that) {
    if (that instanceof SpecValueCounter)
      return this.equals((SpecValueCounter)that);
    return false;
  }

  public boolean equals(SpecValueCounter that) {
    if (that == null)
      return false;
    if (this == that)
      return true;

    boolean this_present_comp = true && this.isSetComp();
    boolean that_present_comp = true && that.isSetComp();
    if (this_present_comp || that_present_comp) {
      if (!(this_present_comp && that_present_comp))
        return false;
      if (!this.comp.equals(that.comp))
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

    hashCode = hashCode * 8191 + ((isSetComp()) ? 131071 : 524287);
    if (isSetComp())
      hashCode = hashCode * 8191 + comp.getValue();

    hashCode = hashCode * 8191 + org.apache.thrift.TBaseHelper.hashCode(v);

    return hashCode;
  }

  @Override
  public int compareTo(SpecValueCounter other) {
    if (!getClass().equals(other.getClass())) {
      return getClass().getName().compareTo(other.getClass().getName());
    }

    int lastComparison = 0;

    lastComparison = java.lang.Boolean.compare(isSetComp(), other.isSetComp());
    if (lastComparison != 0) {
      return lastComparison;
    }
    if (isSetComp()) {
      lastComparison = org.apache.thrift.TBaseHelper.compareTo(this.comp, other.comp);
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
    java.lang.StringBuilder sb = new java.lang.StringBuilder("SpecValueCounter(");
    boolean first = true;

    sb.append("comp:");
    if (this.comp == null) {
      sb.append("null");
    } else {
      sb.append(this.comp);
    }
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

  private static class SpecValueCounterStandardSchemeFactory implements org.apache.thrift.scheme.SchemeFactory {
    @Override
    public SpecValueCounterStandardScheme getScheme() {
      return new SpecValueCounterStandardScheme();
    }
  }

  private static class SpecValueCounterStandardScheme extends org.apache.thrift.scheme.StandardScheme<SpecValueCounter> {

    @Override
    public void read(org.apache.thrift.protocol.TProtocol iprot, SpecValueCounter struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TField schemeField;
      iprot.readStructBegin();
      while (true)
      {
        schemeField = iprot.readFieldBegin();
        if (schemeField.type == org.apache.thrift.protocol.TType.STOP) { 
          break;
        }
        switch (schemeField.id) {
          case 1: // COMP
            if (schemeField.type == org.apache.thrift.protocol.TType.I32) {
              struct.comp = org.swcdb.thrift.gen.Comp.findByValue(iprot.readI32());
              struct.setCompIsSet(true);
            } else { 
              org.apache.thrift.protocol.TProtocolUtil.skip(iprot, schemeField.type);
            }
            break;
          case 2: // V
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
    public void write(org.apache.thrift.protocol.TProtocol oprot, SpecValueCounter struct) throws org.apache.thrift.TException {
      struct.validate();

      oprot.writeStructBegin(STRUCT_DESC);
      if (struct.comp != null) {
        oprot.writeFieldBegin(COMP_FIELD_DESC);
        oprot.writeI32(struct.comp.getValue());
        oprot.writeFieldEnd();
      }
      oprot.writeFieldBegin(V_FIELD_DESC);
      oprot.writeI64(struct.v);
      oprot.writeFieldEnd();
      oprot.writeFieldStop();
      oprot.writeStructEnd();
    }

  }

  private static class SpecValueCounterTupleSchemeFactory implements org.apache.thrift.scheme.SchemeFactory {
    @Override
    public SpecValueCounterTupleScheme getScheme() {
      return new SpecValueCounterTupleScheme();
    }
  }

  private static class SpecValueCounterTupleScheme extends org.apache.thrift.scheme.TupleScheme<SpecValueCounter> {

    @Override
    public void write(org.apache.thrift.protocol.TProtocol prot, SpecValueCounter struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TTupleProtocol oprot = (org.apache.thrift.protocol.TTupleProtocol) prot;
      java.util.BitSet optionals = new java.util.BitSet();
      if (struct.isSetComp()) {
        optionals.set(0);
      }
      if (struct.isSetV()) {
        optionals.set(1);
      }
      oprot.writeBitSet(optionals, 2);
      if (struct.isSetComp()) {
        oprot.writeI32(struct.comp.getValue());
      }
      if (struct.isSetV()) {
        oprot.writeI64(struct.v);
      }
    }

    @Override
    public void read(org.apache.thrift.protocol.TProtocol prot, SpecValueCounter struct) throws org.apache.thrift.TException {
      org.apache.thrift.protocol.TTupleProtocol iprot = (org.apache.thrift.protocol.TTupleProtocol) prot;
      java.util.BitSet incoming = iprot.readBitSet(2);
      if (incoming.get(0)) {
        struct.comp = org.swcdb.thrift.gen.Comp.findByValue(iprot.readI32());
        struct.setCompIsSet(true);
      }
      if (incoming.get(1)) {
        struct.v = iprot.readI64();
        struct.setVIsSet(true);
      }
    }
  }

  private static <S extends org.apache.thrift.scheme.IScheme> S scheme(org.apache.thrift.protocol.TProtocol proto) {
    return (org.apache.thrift.scheme.StandardScheme.class.equals(proto.getScheme()) ? STANDARD_SCHEME_FACTORY : TUPLE_SCHEME_FACTORY).getScheme();
  }
}

