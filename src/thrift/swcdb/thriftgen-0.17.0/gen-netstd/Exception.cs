/**
 * <auto-generated>
 * Autogenerated by Thrift Compiler (0.17.0)
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 * </auto-generated>
 */
using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;
using Thrift;
using Thrift.Collections;
using Thrift.Protocol;
using Thrift.Protocol.Entities;
using Thrift.Protocol.Utilities;
using Thrift.Transport;
using Thrift.Transport.Client;
using Thrift.Transport.Server;
using Thrift.Processor;


#pragma warning disable IDE0079  // remove unnecessary pragmas
#pragma warning disable IDE0017  // object init can be simplified
#pragma warning disable IDE0028  // collection init can be simplified
#pragma warning disable IDE1006  // parts of the code use IDL spelling
#pragma warning disable CA1822   // empty DeepCopy() methods still non-static
#pragma warning disable IDE0083  // pattern matching "that is not SomeType" requires net5.0 but we still support earlier versions


/// <summary>
/// The SWC::Thrift::Exception a base for any Exceptions
/// both for the Thrift-Protocol and SWC-DB Errors.
/// </summary>
public partial class Exception : TException, TBase
{
  private int _code;
  private string _message;

  /// <summary>
  /// The corresponding Thrift-Procotol or SWC-DB Error Code
  /// </summary>
  public int Code
  {
    get
    {
      return _code;
    }
    set
    {
      __isset.code = true;
      this._code = value;
    }
  }

  /// <summary>
  /// The message describing the error code
  /// </summary>
  public string Message
  {
    get
    {
      return _message;
    }
    set
    {
      __isset.message = true;
      this._message = value;
    }
  }


  public Isset __isset;
  public struct Isset
  {
    public bool code;
    public bool message;
  }

  public Exception()
  {
  }

  public Exception DeepCopy()
  {
    var tmp0 = new Exception();
    if(__isset.code)
    {
      tmp0.Code = this.Code;
    }
    tmp0.__isset.code = this.__isset.code;
    if((Message != null) && __isset.message)
    {
      tmp0.Message = this.Message;
    }
    tmp0.__isset.message = this.__isset.message;
    return tmp0;
  }

  public async global::System.Threading.Tasks.Task ReadAsync(TProtocol iprot, CancellationToken cancellationToken)
  {
    iprot.IncrementRecursionDepth();
    try
    {
      TField field;
      await iprot.ReadStructBeginAsync(cancellationToken);
      while (true)
      {
        field = await iprot.ReadFieldBeginAsync(cancellationToken);
        if (field.Type == TType.Stop)
        {
          break;
        }

        switch (field.ID)
        {
          case 1:
            if (field.Type == TType.I32)
            {
              Code = await iprot.ReadI32Async(cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          case 2:
            if (field.Type == TType.String)
            {
              Message = await iprot.ReadStringAsync(cancellationToken);
            }
            else
            {
              await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            }
            break;
          default: 
            await TProtocolUtil.SkipAsync(iprot, field.Type, cancellationToken);
            break;
        }

        await iprot.ReadFieldEndAsync(cancellationToken);
      }

      await iprot.ReadStructEndAsync(cancellationToken);
    }
    finally
    {
      iprot.DecrementRecursionDepth();
    }
  }

  public async global::System.Threading.Tasks.Task WriteAsync(TProtocol oprot, CancellationToken cancellationToken)
  {
    oprot.IncrementRecursionDepth();
    try
    {
      var tmp1 = new TStruct("Exception");
      await oprot.WriteStructBeginAsync(tmp1, cancellationToken);
      var tmp2 = new TField();
      if(__isset.code)
      {
        tmp2.Name = "code";
        tmp2.Type = TType.I32;
        tmp2.ID = 1;
        await oprot.WriteFieldBeginAsync(tmp2, cancellationToken);
        await oprot.WriteI32Async(Code, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      if((Message != null) && __isset.message)
      {
        tmp2.Name = "message";
        tmp2.Type = TType.String;
        tmp2.ID = 2;
        await oprot.WriteFieldBeginAsync(tmp2, cancellationToken);
        await oprot.WriteStringAsync(Message, cancellationToken);
        await oprot.WriteFieldEndAsync(cancellationToken);
      }
      await oprot.WriteFieldStopAsync(cancellationToken);
      await oprot.WriteStructEndAsync(cancellationToken);
    }
    finally
    {
      oprot.DecrementRecursionDepth();
    }
  }

  public override bool Equals(object that)
  {
    if (!(that is Exception other)) return false;
    if (ReferenceEquals(this, other)) return true;
    return ((__isset.code == other.__isset.code) && ((!__isset.code) || (global::System.Object.Equals(Code, other.Code))))
      && ((__isset.message == other.__isset.message) && ((!__isset.message) || (global::System.Object.Equals(Message, other.Message))));
  }

  public override int GetHashCode() {
    int hashcode = 157;
    unchecked {
      if(__isset.code)
      {
        hashcode = (hashcode * 397) + Code.GetHashCode();
      }
      if((Message != null) && __isset.message)
      {
        hashcode = (hashcode * 397) + Message.GetHashCode();
      }
    }
    return hashcode;
  }

  public override string ToString()
  {
    var tmp3 = new StringBuilder("Exception(");
    int tmp4 = 0;
    if(__isset.code)
    {
      if(0 < tmp4++) { tmp3.Append(", "); }
      tmp3.Append("Code: ");
      Code.ToString(tmp3);
    }
    if((Message != null) && __isset.message)
    {
      if(0 < tmp4++) { tmp3.Append(", "); }
      tmp3.Append("Message: ");
      Message.ToString(tmp3);
    }
    tmp3.Append(')');
    return tmp3.ToString();
  }
}

