/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include "qtlockedfile.hpp"

namespace MellowPlayer::Infrastructure
{
    /*!
        \class QtLockedFile

        \brief The QtLockedFile class extends QFile with advisory locking functions.

        A file may be locked in read or write mode. Multiple instances of
        \e QtLockedFile, created in multiple processes running on the same
        machine, may have a file locked in read mode. Exactly one instance
        may have it locked in write mode. A read and a write lock cannot
        exist simultaneously on the same file.

        The file locks are advisory. This means that nothing prevents
        another process from manipulating a locked file using QFile or
        file system functions offered by the OS. Serialization is only
        guaranteed if all processes that access the file use
        QtLockedFile. Also, while holding a lock on a file, a process
        must not open the same file again (through any API), or locks
        can be unexpectedly lost.

        The lock provided by an instance of \e QtLockedFile is released
        whenever the program terminates. This is true even when the
        program crashes and no destructors are called.
    */

    /*! \enum QtLockedFile::LockMode

        This enum describes the available lock modes.

        \value ReadLock A read lock.
        \value WriteLock A write lock.
        \value NoLock Neither a read lock nor a write lock.
    */

    /*!
        Constructs an unlocked \e QtLockedFile object. This constructor behaves in the same way
        as \e QFile::QFile().

        \sa QFile::QFile()
    */
    QtLockedFile::QtLockedFile() : QFile()
    {
#ifdef Q_OS_WIN
        m_semaphore_hnd = 0;
        m_mutex_hnd = 0;
#endif
        m_lock_mode = NoLock;
    }

    /*!
        Constructs an unlocked QtLockedFile object with file \a name. This constructor behaves in
        the same way as \e QFile::QFile(const QString&).

        \sa QFile::QFile()
    */
    QtLockedFile::QtLockedFile(const QString &name) : QFile(name)
    {
#ifdef Q_OS_WIN
        m_semaphore_hnd = 0;
        m_mutex_hnd = 0;
#endif
        m_lock_mode = NoLock;
    }

    /*!
        Returns \e true if this object has a in read or write lock;
        otherwise returns \e false.

        \sa lockMode()
    */
    bool QtLockedFile::isLocked() const
    {
        return m_lock_mode != NoLock;
    }

    /*!
        Returns the type of lock currently held by this object, or \e QtLockedFile::NoLock.

        \sa isLocked()
    */
    QtLockedFile::LockMode QtLockedFile::lockMode() const
    {
        return m_lock_mode;
    }

    /*!
        \fn bool QtLockedFile::lock(LockMode mode, bool block = true)

        Obtains a lock of type \a mode.

        If \a block is true, this
        function will block until the lock is acquired. If \a block is
        false, this function returns \e false immediately if the lock cannot
        be acquired.

        If this object already has a lock of type \a mode, this function returns \e true immediately. If this object has a lock of a different type than \a
       mode, the lock is first released and then a new lock is obtained.

        This function returns \e true if, after it executes, the file is locked by this object,
        and \e false otherwise.

        \sa unlock(), isLocked(), lockMode()
    */

    /*!
        \fn bool QtLockedFile::unlock()

        Releases a lock.

        If the object has no lock, this function returns immediately.

        This function returns \e true if, after it executes, the file is not locked by
        this object, and \e false otherwise.

        \sa lock(), isLocked(), lockMode()
    */

    /*!
        \fn QtLockedFile::~QtLockedFile()

        Destroys the \e QtLockedFile object. If any locks were held, they are released.
    */

}  // namespace MellowPlayer::Infrastructure

#ifdef Q_OS_WIN

#    include "qtlockedfile.hpp"

#    include <QFileInfo>
#    include <qt_windows.h>

namespace MellowPlayer::Infrastructure
{
#    define SEMAPHORE_PREFIX "QtLockedFile semaphore "
#    define MUTEX_PREFIX "QtLockedFile mutex "
#    define SEMAPHORE_MAX 100

    static QString errorCodeToString(DWORD errorCode)
    {
        QString result;
        char *data = 0;
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, 0, errorCode, 0, (char *) &data, 0, 0);
        result = QString::fromLocal8Bit(data);
        if (data != 0)
            LocalFree(data);

        if (result.endsWith(QLatin1Char('\n')))
            result.truncate(result.length() - 1);

        return result;
    }

    bool QtLockedFile::lock(LockMode mode, bool block)
    {
        if (!isOpen())
        {
            qWarning("QtLockedFile::lock(): file is not opened");
            return false;
        }

        if (mode == m_lock_mode)
            return true;

        if (m_lock_mode != 0)
            unlock();

        if (m_semaphore_hnd == 0)
        {
            QFileInfo fi(*this);
            QString sem_name = QString::fromLatin1(SEMAPHORE_PREFIX) + fi.absoluteFilePath().toLower();

            m_semaphore_hnd = CreateSemaphoreW(0, SEMAPHORE_MAX, SEMAPHORE_MAX, (TCHAR *) sem_name.utf16());

            if (m_semaphore_hnd == 0)
            {
                qWarning("QtLockedFile::lock(): CreateSemaphore: %s", errorCodeToString(GetLastError()).toLatin1().constData());
                return false;
            }
        }

        bool gotMutex = false;
        int decrement;
        if (mode == ReadLock)
        {
            decrement = 1;
        }
        else
        {
            decrement = SEMAPHORE_MAX;
            if (m_mutex_hnd == 0)
            {
                QFileInfo fi(*this);
                QString mut_name = QString::fromLatin1(MUTEX_PREFIX) + fi.absoluteFilePath().toLower();

                m_mutex_hnd = CreateMutexW(nullptr, FALSE, (TCHAR *) mut_name.utf16());

                if (m_mutex_hnd == 0)
                {
                    qWarning("QtLockedFile::lock(): CreateMutex: %s", errorCodeToString(GetLastError()).toLatin1().constData());
                    return false;
                }
            }
            DWORD res = WaitForSingleObject(m_mutex_hnd, block ? INFINITE : 0);
            if (res == WAIT_TIMEOUT)
                return false;
            if (res == WAIT_FAILED)
            {
                qWarning("QtLockedFile::lock(): WaitForSingleObject (mutex): %s", errorCodeToString(GetLastError()).toLatin1().constData());
                return false;
            }
            gotMutex = true;
        }

        for (int i = 0; i < decrement; ++i)
        {
            DWORD res = WaitForSingleObject(m_semaphore_hnd, block ? INFINITE : 0);
            if (res == WAIT_TIMEOUT)
            {
                if (i)
                {
                    // A failed nonblocking rw locking. Undo changes to semaphore.
                    if (ReleaseSemaphore(m_semaphore_hnd, i, nullptr) == 0)
                    {
                        qWarning("QtLockedFile::unlock(): ReleaseSemaphore: %s", errorCodeToString(GetLastError()).toLatin1().constData());
                        // Fall through
                    }
                }
                if (gotMutex)
                    ReleaseMutex(m_mutex_hnd);
                return false;
            }
            if (res != WAIT_OBJECT_0)
            {
                if (gotMutex)
                    ReleaseMutex(m_mutex_hnd);
                qWarning("QtLockedFile::lock(): WaitForSingleObject (semaphore): %s", errorCodeToString(GetLastError()).toLatin1().constData());
                return false;
            }
        }

        m_lock_mode = mode;
        if (gotMutex)
            ReleaseMutex(m_mutex_hnd);
        return true;
    }

    bool QtLockedFile::unlock()
    {
        if (!isOpen())
        {
            qWarning("QtLockedFile::unlock(): file is not opened");
            return false;
        }

        if (!isLocked())
            return true;

        int increment;
        if (m_lock_mode == ReadLock)
            increment = 1;
        else
            increment = SEMAPHORE_MAX;

        DWORD ret = ReleaseSemaphore(m_semaphore_hnd, increment, 0);
        if (ret == 0)
        {
            qWarning("QtLockedFile::unlock(): ReleaseSemaphore: %s", errorCodeToString(GetLastError()).toLatin1().constData());
            return false;
        }

        m_lock_mode = QtLockedFile::NoLock;
        remove();
        return true;
    }

    QtLockedFile::~QtLockedFile()
    {
        if (isOpen())
            unlock();
        if (m_mutex_hnd != 0)
        {
            DWORD ret = CloseHandle(m_mutex_hnd);
            if (ret == 0)
            {
                qWarning("QtLockedFile::~QtLockedFile(): CloseHandle (mutex): %s", errorCodeToString(GetLastError()).toLatin1().constData());
            }
            m_mutex_hnd = 0;
        }
        if (m_semaphore_hnd != 0)
        {
            DWORD ret = CloseHandle(m_semaphore_hnd);
            if (ret == 0)
            {
                qWarning("QtLockedFile::~QtLockedFile(): CloseHandle (semaphore): %s", errorCodeToString(GetLastError()).toLatin1().constData());
            }
            m_semaphore_hnd = 0;
        }
    }

}  // namespace MellowPlayer::Infrastructure
#else

#include "qtlockedfile.hpp"

#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>

namespace MellowPlayer::Infrastructure {

    bool QtLockedFile::lock(LockMode mode, bool block)
    {
        if (!isOpen()) {
            qWarning("QtLockedFile::lock(): file is not opened");
            return false;
        }

        if (mode == NoLock)
            return unlock();

        if (mode == m_lock_mode)
            return true;

        if (m_lock_mode != NoLock)
            unlock();

        struct flock fl;
        fl.l_whence = SEEK_SET;
        fl.l_start = 0;
        fl.l_len = 0;
        fl.l_type = (mode == ReadLock) ? F_RDLCK : F_WRLCK;
        int cmd = block ? F_SETLKW : F_SETLK;
        int ret = fcntl(handle(), cmd, &fl);

        if (ret == -1) {
            if (errno != EINTR && errno != EAGAIN)
                qWarning("QtLockedFile::lock(): fcntl: %s", strerror(errno));
            return false;
        }


        m_lock_mode = mode;
        return true;
    }


    bool QtLockedFile::unlock()
    {
        if (!isOpen()) {
            qWarning("QtLockedFile::unlock(): file is not opened");
            return false;
        }

        if (!isLocked())
            return true;

        struct flock fl;
        fl.l_whence = SEEK_SET;
        fl.l_start = 0;
        fl.l_len = 0;
        fl.l_type = F_UNLCK;
        int ret = fcntl(handle(), F_SETLKW, &fl);

        if (ret == -1) {
            qWarning("QtLockedFile::lock(): fcntl: %s", strerror(errno));
            return false;
        }

        m_lock_mode = NoLock;
        remove();
        return true;
    }

    QtLockedFile::~QtLockedFile()
    {
        if (isOpen())
            unlock();
    }

} // namespace MellowPlayer::Infrastructure

#endif